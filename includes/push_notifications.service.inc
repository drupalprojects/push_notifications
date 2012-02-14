<?php

/**
 * @file
 * Services callbacks.
 */

/**
 * Service callback to store a device token.
 *
 * @params $data
 *   Array with the following keys:
 *   - token
 *   - type
 *
 * @return
 *   Service data
 */
function _push_notifications_service_create_device_token($data) {
  if (!isset($data['token']) || !isset($data['type'])) {
    return services_error(t('At least one parameter is missing.'), 400);
  }

  // Decode data.
  $token = $data['token'];
  $type = $data['type'];

  // Get the current user id.
  $uid = $GLOBALS['user']->uid;
  // Remove empty spaces from the token.
  $token = str_replace(' ', '', $token);
  // Convert type to integer value.
  if ($type != 'ios' && $type != 'android') {
    return services_error(t('Type not supported.'), 400);
  }
  else {
    $type_id = ($type == 'ios') ? PUSH_NOTIFICATIONS_TYPE_ID_IOS : PUSH_NOTIFICATIONS_TYPE_ID_ANDROID;
  }

  // Determine if this token is already registered with the current user.
  if (push_notifications_find_token($token, $uid)) {
    return array(
      'success' => 1,
      'message' => 'This token is already registered to this user.'
    );
  }

  // Store this token in the database.
  $result = push_notifications_store_token($token, $type_id, $uid);

  if ($result === FALSE) {
    return services_error(t('This token could not be stored.'), 400);
  }
  else {
    return array(
      'success' => 1,
      'message' => 'This token was successfully stored in the database.'
    );
  }
}