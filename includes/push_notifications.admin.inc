<?php

/**
 * @file
 * Admin files for Push Notifications module.
 */

/**
 * Overview form for Push Notification Settings.
 */
function push_notifications_admin_overview_form($form_state) {
  // Load all tokens stored in the database.
  $query = db_select('push_notifications_tokens', 'pnt');
  $query->fields('pnt', array('uid', 'type', 'language'));
  $result = $query->execute();
  $counts = array(
    'total' => 0,
    'ios' => 0,
    'android' => 0,
    'anonymous' => 0,
    'registered' => 0,
  );

  foreach ($result as $data) {
    $counts['total']++;
    switch ($data->type) {
      case PUSH_NOTIFICATIONS_TYPE_ID_IOS: $counts['ios']++; break;
      case PUSH_NOTIFICATIONS_TYPE_ID_ANDROID: $counts['android']++; break;
    }
    if ($data->uid == 0) {
      $counts['anonymous']++;
    }
    else {
      $counts['registered']++;
    }
  }

  $form = array();

  $statistics_description = (!$counts['total']) ? t('No tokens stored yet.') : null;
  $form['statistics'] = array(
    '#type' => 'fieldset',
    '#title' => 'Push Notification Statistics',
    '#description' => $statistics_description,
  );

  $form['statistics']['total'] = array(
    '#type' => 'item',
    '#title' => t('Total Tokens Stored'),
    '#markup' => $counts['total'],
  );

  $form['statistics']['ios'] = array(
    '#type' => 'item',
    '#title' => t('iOS Tokens Stored'),
    '#markup' => $counts['ios'],
  );

  $form['statistics']['android'] = array(
    '#type' => 'item',
    '#title' => t('Android Tokens Stored'),
    '#markup' => $counts['android'],
  );

  $form['statistics']['anonymous'] = array(
    '#type' => 'item',
    '#title' => t('Anonymous Tokens Stored'),
    '#markup' => $counts['anonymous'],
  );

  $form['statistics']['registered'] = array(
    '#type' => 'item',
    '#title' => t('Registered Tokens Stored'),
    '#markup' => $counts['registered'],
  );

  $form['languages'] = array(
    '#type' => 'fieldset',
    '#title' => 'Push Notification Languages',
    '#description' => t('Languages used across all push notification recipients'),
  );

  // Determine which languages are used.
  $languages_used = push_notifications_used_languages();
  if (!empty($languages_used)) {
    unset($languages_used[0]);
    $languages_markup = theme('item_list', array('items' => $languages_used));
  }
  else {
    $languages_markup = t('No tokens stored or no tokens with a language association stored');
  }

  $form['languages']['used'] = array(
    '#type' => 'item',
    '#markup' => $languages_markup,
  );

  return $form;
}

/**
 * Form callback for Push Notifications Settings.
 */
function push_notifications_admin_form($form_state) {
  $form = array();

  $form['configuration_general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Push Notifications Settings'),
  );

  $form['configuration_general']['push_notifications_require_enabled_language'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only allow enabled languages'),
    '#description' => t('When setting a device token, only allow languages that are enabled on this site (instead of all valid langauges)'),
    '#default_value' => variable_get('push_notifications_require_enabled_language', 0),
  );

  $configuration_apns_replacements = array(
    '!link' => l(t('this tutorial'), 'http://blog.boxedice.com/2009/07/10/how-to-build-an-apple-push-notification-provider-server-tutorial/', array('attributes' => array('target' => '_blank'))),
  );
  $form['configuration_apns'] = array(
    '#type' => 'fieldset',
    '#title' => t('Apple Push Notifications'),
    '#description' => t('Configure Push Notifications for Apple\'s Push Notification Server. Select your environment. Both environments require the proper certificates in the \'certificates\' folder of this module. The filename for the development certificate should be \'apns-development.pem\', the production certificate should be \'apns-production.pem\'. See !link for instructions on creating certificates.', $configuration_apns_replacements),
  );

  $form['configuration_apns']['push_notifications_apns_environment'] = array(
    '#type' => 'select',
    '#title' => t('APNS Environment'),
    '#description' => t('Select the active APNS Environment. Please note that development certificates do not work with apps released in the Apple app store; production certificates only work with apps released in the app store.'),
    '#options' => array(
      0 => 'Development',
      1 => 'Production',
    ),
    '#default_value' => variable_get('push_notifications_apns_environment', 0),
  );

  $form['configuration_apns']['stream_context_limit'] = array(
    '#type' => 'select',
    '#title' => t('Stream Context Limit'),
    '#description' => t('Defines the amount of messages sent per stream limit. Unclear (to me) what Apple\'s <em>actual</em> limit is. The higher the limit, the faster the message delivery. If the limit is too high, messages might not get delivered at all.'),
    '#options' => drupal_map_assoc(array(1, 5, 10, 25, 50)),
    '#default_value' => variable_get('push_notifications_apns_stream_context_limit', 5),
  );

  $form['configuration_c2dm'] = array(
    '#type' => 'fieldset',
    '#title' => t('C2DM Push Notifications'),
    '#description' => t('Requires a valid C2DM Google Account. !signup to enable a Google Account for C2DM.', array('!signup' => l(t('Signup here'), 'http://code.google.com/android/c2dm/signup.html', array('attributes' => array('target' => '_blank'))))),
  );

  $form['configuration_c2dm']['push_notifications_c2dm_username'] = array(
    '#type' => 'textfield',
    '#title' => t('C2DM Username'),
    '#description' => t('Enter the username for your C2DM Google Account'),
    '#default_value' => variable_get('push_notifications_c2dm_username', ''),
  );

  $form['configuration_c2dm']['push_notifications_c2dm_password'] = array(
    '#type' => 'textfield',
    '#title' => t('C2DM Password'),
    '#description' => t('Enter the password for your C2DM Google Account'),
    '#default_value' => variable_get('push_notifications_c2dm_password', ''),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save Configuration',
  );

  return $form;
}



/**
 * Submit callback for push notification configuration page.
 */
function push_notifications_admin_form_submit($form, &$form_state) {
  variable_set('push_notifications_require_enabled_language', $form_state['values']['push_notifications_require_enabled_language']);

  $apns_environment = $form_state['values']['push_notifications_apns_environment'];
  switch ($apns_environment) {
    // Development Environment.
    case 0:
      // Set the variables for the apns development environment.
      variable_set('push_notifications_apns_environment', $apns_environment);
      // Set the individual variables.
      variable_set('push_notifications_apns_host', 'gateway.sandbox.push.apple.com');
      variable_set('push_notifications_apns_certificate', 'apns-development.pem');
      break;
    case 1:
      // Set the variables for the apns production environment.
      variable_set('push_notifications_apns_environment', $apns_environment);
      // Set the individual variables.
      variable_set('push_notifications_apns_host', 'gateway.push.apple.com');
      variable_set('push_notifications_apns_certificate', 'apns-production.pem');
      break;
  }

  // Set C2DM credentials.
  variable_set('push_notifications_c2dm_username', $form_state['values']['push_notifications_c2dm_username']);
  variable_set('push_notifications_c2dm_password', $form_state['values']['push_notifications_c2dm_password']);

  // Set the APNS stream limit.
  variable_set('push_notifications_apns_stream_context_limit', $form_state['values']['stream_context_limit']);

  $replacements = array(
    '@environment' => ($apns_environment) ? "Production" : "Development",
  );
  drupal_set_message(t('The APNS environment was successfully set to "@environment".', $replacements));
}



/**
 * Form callback for sending a mass-push notification.
 */
function push_notifications_mass_push_form($form_state) {
  $form = array();

  $form['message'] = array(
    '#type' => 'fieldset',
    '#title' => t('Push Notification Message'),
    '#description' => t('Compose the elements of your push notification message.'),
    '#tree' => TRUE,
  );

  $form['message']['alert'] = array(
    '#type' => 'textfield',
    '#title' => t('Push Message'),
    '#description' => t('Compose the message to send out (256 characters max.)'),
    '#default_value' => (isset($form_state['values']['message']['alert'])) ? $form_state['values']['message']['alert'] : '',
    '#required' => TRUE,
    '#size' => 128,
    '#maxlength' => 256,
    '#weight' => 10,
  );

  $form['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#options' => push_notifications_used_languages(),
    '#description' => t('Optionally, only select the push notifications to recipients with this language.'),
    '#default_value' => (isset($form_state['values']['language'])) ? $form_state['values']['language'] : '',
    '#weight' => 12,
  );

  // Only show Android option if C2DM credentials are available.
  $recipients_options = array('ios' => t('iOS (iPhone/iPad)'));
  if (PUSH_NOTIFICATIONS_C2DM_USERNAME && PUSH_NOTIFICATIONS_C2DM_PASSWORD) {
    $recipients_options['android'] = t('Android');
  }
  $form['recipients'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Recipients'),
    '#description' => t('Select the recipients for this push message'),
    '#options' => $recipients_options,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Send Push Notification',
    '#weight' => 50,
  );

  return $form;
}



/**
 * Submit handler for sending out a mass-push notification.
 */
function push_notifications_mass_push_form_validate($form, &$form_state) {
  $recipients = $form_state['values']['recipients'];

  // Define an empty array for the payload.
  $payload = array();

  // Add all "message" elements to the payload.
  // Other modules can alter the contents of the payload
  // array by adding additional elements to 'message'
  // when it implements hook_form_alter.
  $message_elements = $form_state['values']['message'];
  foreach ($message_elements as $key => $value) {
    $payload[$key] = $value;
  }

  // Store payload in the form_state.
  $form_state['values']['payload'] = $payload;

  // Make sure at least one recipient (group) is selected.
  if (empty($recipients['ios']) && empty($recipients['android'])) {
    form_set_error('recipients', t('No message was sent. Please select at least one recipient group.'));
  }

  // Validate that the message size is ok.
  if (!push_notifications_check_payload_size($form_state['values']['payload'])) {
    form_set_error('message', t('Your message exceeds the allowed size of 256 bytes. Please shorten your message.'));
  }
}



/**
 * Submit handler for sending out a mass-push notification.
 */
function push_notifications_mass_push_form_submit($form, &$form_state) {
  $recipients = $form_state['values']['recipients'];
  $payload = $form_state['values']['payload'];
  $language = $form_state['values']['language'];

  // Send message to all iOS recipients.
  if (!empty($recipients['ios'])) {
    // Get all iOS recipients.
    $tokens_ios = push_notifications_get_tokens(PUSH_NOTIFICATIONS_TYPE_ID_IOS, $language);
    if (!empty($tokens_ios)) {
      $result = push_notifications_apns_send_message($tokens_ios, $payload);
      $dsm_type = ($result['success']) ? 'status' : 'error';
      drupal_set_message($result['message'], $dsm_type);
    }
    else {
      drupal_set_message(t('No iOS recipients found, potentially for this language.'));
    }
  }

  // Send message to all Android recipients.
  if (!empty($recipients['android'])) {
    // Get all Android recipients.
    $tokens_android = push_notifications_get_tokens(PUSH_NOTIFICATIONS_TYPE_ID_ANDROID, $language);
    if (!empty($tokens_android)) {
      $result = push_notifications_c2dm_send_message($tokens_android, $payload);
      $dsm_type = ($result['success']) ? 'status' : 'error';
      drupal_set_message($result['message'], $dsm_type);
    }
    else {
      drupal_set_message(t('No Android recipients found, potentially for this language.'));
    }
  }
}
