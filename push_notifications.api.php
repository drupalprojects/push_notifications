<?php

/**
 * @file
 * Hooks provided by Push Notifications.
 */

/**
 * @addtogroup hooks
 */

/**
 * Allows a module to modify the token before it is stored in the database.
 *
 * @return
 *   By reference, the token to be stored.
 *
 *
 * @param string &$token The device token to be stored.
 * @param int $type_id Either 1 or 0 depending on the type of device.
 * @param int $uid The user for whom the token is to be stored. Defaults to the
 * currently logged in user.
 */
function hook_push_notifications_store_token(&$token, $type_id, $uid) {
  // If a value exists, stop the writing of the token.
  if ($value) {
    $token = NULL;
  }
}

/**
 * Allows a module to respond to a token being purged.
 *
 * @param string $token
 *   Token being purged.
 * @param int $type_id
 *   Device type id.
 *
 */
function hook_push_notifications_purge_token($token, $type_id) {

}

/**
 * Allows a module to use the newly created record
 * after a token was stored in the database.
 *
 * @param object $token_record Database record containing the token.
 *
 */
function hook_push_notifications_post_store_token($token_record) {

}
