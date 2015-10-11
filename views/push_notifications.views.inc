<?php

/**
* Expose Push Notifications data to views.
*/
function push_notifications_views_data() {
  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['push_notifications_tokens']['table'] = array(
    'group' => t('Push Notifications'),
    'title' => t('Push Tokens'),
    'help' => t('List of stored push tokens.'),
  );

  // Define this as a base table.
  $data['push_notifications_tokens']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Push Token'),
    'help' => t("Push tokens are unique identifiers for an app."),
    'weight' => -10,
  );

  // Push Token.
  $data['push_notifications_tokens']['token'] = array(
    'title' => t('Token'),
    'help' => t('Push Token.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // User ID associated with this token.
  $data['push_notifications_tokens']['uid'] = array(
    'title' => t('User ID Token Owner'),
    'help' => t('UID associated with this token'),
    'field' => array(
      'handler' => 'views_handler_field_user',
    ),
    'relationship' => array(
      'title' => t('User'),
      'help' => t("The User ID of token owner."),
      'base' => 'users',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Device Type.
  $data['push_notifications_tokens']['type'] = array(
    'title' => t('Device Type'),
    'help' => t('Device Type (iOS or Android)'),
    'field' => array(
      'handler' => 'push_notifications_views_handler_field_push_notifications_type',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'push_notifications_views_handler_filter_push_notifications_type',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Timestamp.
  $data['push_notifications_tokens']['timestamp'] = array(
    'title' => t('Timestamp'),
    'help' => t('Timestamp this token was created / last updated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // Language.
  if (module_exists('locale')) {
    $data['push_notifications_tokens']['language'] = array(
      'title' => t('Language'),
      'help' => t('The language the comment is in.'),
      'field' => array(
        'handler' => 'views_handler_field_locale_language',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_locale_language',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_locale_language',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );
  }

  return $data;
}


/**
 * Implements hook_views_handlers().
 */
function push_notifications_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'push_notifications') . '/views',
    ),
    'handlers' => array(
      'push_notifications_views_handler_filter_push_notifications_type' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'push_notifications_views_handler_field_push_notifications_type' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}
