<?php
/**
 * @file
 * Administration Events Rule for Push Notifications.
 */


/**
 * Implements hook_rules_action_info().
 */
function push_notifications_rules_action_info() {
  $items = array();

  $items['push_notifications_send_message_account'] = array(
    'label' => t('Send a push notification to a user account'),
    'group' => t('Push notification'),
    'parameter' => array(
      'account' => array(
        'type' => 'user',
        'label' => t('User Account'),
        'description' => t('Specify the recipient account for this message.'),
      ),
      'message' => array(
        'type' => 'text',
        'label' => t('Notification message'),
      ),
    ),
  );

  $items['push_notifications_send_message_bulk'] = array(
    'label' => t('Send a push notification to all registered tokens'),
    'group' => t('Push notification'),
    'parameter' => array(
      'message' => array(
        'type' => 'text',
        'label' => t('Notification message'),
      ),
      'target_group' => array(
        'type' => 'text',
        'label' => t('Target Group'),
        'description' => t('Select which user group this message should be delivered to.'),
        'options list' => 'push_notifications_target_group_options',
        'restriction' => 'input',
        'default value' => 'any',
        'optional' => TRUE,
      ),
    ),
  );

  return $items;
}

/**
 * Defines target groups for bulk message alert.
 *
 * @return array
 */
function push_notifications_target_group_options() {
  return array(
    'any' => t('All tokens'),
    'authenticated' => t('Tokens belonging to authenticated users only'),
    'anonymous' => t('Tokens belonging to anonymous users only'),
  );
}


/**
 * Implements hook_rules_event_info().
 */
function push_notifications_rules_event_info(){
  $events = array();

  $events['push_notifications_before_token_insert'] = array (
    'label' => t('Before saving a new device token'),
    'group' => t('Push Notifications'),
    'module' => 'push_notifications',
    'variables' => array(
      'token' => array('type' => 'text', 'label' => t('token to be inserted')),
      'type_id' => array('type' => 'integer', 'label' => t('type of device: 0 iOS, 1 Android')),
      'uid' => array('type' => 'integer', 'label' => t('User id')),
      'language' => array('type' => 'text', 'label' => t('Language')),
    ),
  );

  $events['push_notifications_after_token_insert'] = array (
    'label' => t('After saving a new device token'),
    'group' => t('Push Notifications'),
    'module' => 'push_notifications',
    'variables' => array(
      'token' => array('type' => 'text', 'label' => t('token to be inserted')),
      'type_id' => array('type' => 'integer', 'label' => t('type of device: 0 iOS, 1 Android')),
      'uid' => array('type' => 'integer', 'label' => t('User id')),
      'language' => array('type' => 'text', 'label' => t('Language')),
      'result' => array('type' => 'integer', 'label' => t('Return value: FALSE for error, SAVED_NEW if succeded')),
    ),
  );

  $events['push_notifications_before_token_delete'] = array (
    'label' => t('Before deleting a device token'),
    'group' => t('Push Notifications'),
    'module' => 'push_notifications',
    'variables' => array(
      'token' => array('type' => 'text', 'label' => t('token to be inserted')),
      'type_id' => array('type' => 'integer', 'label' => t('type of device: 0 iOS, 1 Android')),
    ),
  );

  $events['push_notifications_after_token_delete'] = array (
    'label' => t('After deleting a device token'),
    'group' => t('Push Notifications'),
    'module' => 'push_notifications',
    'variables' => array(
      'token' => array('type' => 'text', 'label' => t('token to be inserted')),
      'type_id' => array('type' => 'integer', 'label' => t('type of device: 0 iOS, 1 Android')),
    ),
  );

  $events['push_notifications_after_apns_feedback'] = array (
    'label' => t('iOS feedback service was completed'),
    'group' => t('Push Notifications'),
    'module' => 'push_notifications',
    'variables' => array(
      'counter' => array('type' => 'integer', 'label' => t('Number of tokens removed')),
    ),
  );


  $events['push_notifications_after_apns_send'] = array (
    'label' => t('After sending an iOS push notification (APNS)'),
    'group' => t('Push Notifications'),
    'module' => 'push_notifications',
    'variables' => array(
      'type_id' => array('type' => 'integer', 'label' => t('type of device: 0 iOS, 1 Android')),
      'payload' => array('type' => 'payload', 'text' => t('Payload sent')),
      'count_attempted' => array('type' => 'integer', 'label' => t('Attempted to send')),
      'count_success' => array('type' => 'integer', 'label' => t('Successfully sent')),
      'success' => array('type' => 'integer', 'label' => t('Result of the sent')),
      'result_message' => array('type' => 'text', 'label' => t('Prepared result message')),
    ),
  );

  $events['push_notifications_after_c2dm_send'] = array (
    'label' => t('After sending an Android push notification (C2DM)'),
    'group' => t('Push Notifications'),
    'module' => 'push_notifications',
    'variables' => array(
      'type_id' => array('type' => 'integer', 'label' => t('type of device: 0 iOS, 1 Android')),
      'payload' => array('type' => 'payload', 'text' => t('Payload sent')),
      'count_attempted' => array('type' => 'integer', 'label' => t('Attempted to send')),
      'count_success' => array('type' => 'integer', 'label' => t('Successfully sent')),
      'success' => array('type' => 'integer', 'label' => t('Result of the sent')),
      'result_message' => array('type' => 'text', 'label' => t('Prepared result message')),
    ),
  );

  $events['push_notifications_after_gcm_send'] = array (
    'label' => t('After sending an Android push notification (GCM)'),
    'group' => t('Push Notifications'),
    'module' => 'push_notifications',
    'variables' => array(
      'type_id' => array('type' => 'integer', 'label' => t('type of device: 0 iOS, 1 Android')),
      'payload' => array('type' => 'payload', 'text' => t('Payload sent')),
      'count_attempted' => array('type' => 'integer', 'label' => t('Attempted to send')),
      'count_success' => array('type' => 'integer', 'label' => t('Successfully sent')),
      'success' => array('type' => 'integer', 'label' => t('Result of the sent')),
      'result_message' => array('type' => 'text', 'label' => t('Prepared result message')),
    ),
  );

  return $events;
}
