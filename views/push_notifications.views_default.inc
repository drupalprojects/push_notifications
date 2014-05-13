<?php

/**
* @file
* Views integration for the push_notifications module.
*/

/**
* Implements hook_views_default_views().
*/
function push_notifications_views_default_views() {
  $view = new view();
  $view->name = 'push_tokens';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'push_notifications_tokens';
  $view->human_name = 'Push Tokens';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'token' => 'token',
    'type' => 'type',
    'timestamp' => 'timestamp',
    'token_1' => 'token_1',
    'uid' => 'uid',
  );
  $handler->display->display_options['style_options']['default'] = 'timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'token' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'token_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Push Notifications: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'push_notifications_tokens';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Push Notifications: User ID Token Owner */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'push_notifications_tokens';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'Uid';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Username';
  /* Field: Push Notifications: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'push_notifications_tokens';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  /* Field: Push Notifications: Token */
  $handler->display->display_options['fields']['token_1']['id'] = 'token_1';
  $handler->display->display_options['fields']['token_1']['table'] = 'push_notifications_tokens';
  $handler->display->display_options['fields']['token_1']['field'] = 'token';
  $handler->display->display_options['fields']['token_1']['alter']['max_length'] = '50';
  $handler->display->display_options['fields']['token_1']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['token_1']['alter']['trim'] = TRUE;
  /* Field: Push Notifications: Device Type ID */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'push_notifications_tokens';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = 'Device Type';
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;

  $views = array();
  $views[$view->name] = $view;
  return $views;
}
