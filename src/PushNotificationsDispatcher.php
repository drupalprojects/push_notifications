<?php

/**
 * @file
 * Contains \Drupal\push_notifications\PushNotificationsDispatcher.
 */

namespace Drupal\push_notifications;

/**
 * Handles dispatching of messages.
 */
class PushNotificationsDispatcher {

  /**
   * Array of tokens grouped by type.
   */
  protected $tokens = array();

  /**
   * Message.
   */
  protected $message;

  /**
   * Constructor.
   */
  public function __construct() {
  }

  /**
   * Dispatch message.
   */
  public function dispatch() {
    // Send payload to iOS recipients.
    if (!empty($this->tokens[PUSH_NOTIFICATIONS_TYPE_ID_IOS])) {
      try {
        $apnsBroadcaster = \Drupal::service('push_notifications.broadcaster_apns');
        $apnsBroadcaster->setTokens($this->tokens[PUSH_NOTIFICATIONS_TYPE_ID_IOS]);
        $apnsBroadcaster->setMessage($this->message);
        $apnsBroadcaster->sendBroadcast();
        $results = $apnsBroadcaster->getResults();
        // TODO: Log results.
      } catch (\Exception $e) {
        //drupal_set_message(t('Your message could not be sent. Please check the log for details.'), 'error');
        \Drupal::logger('push_notifications')->error($e->getMessage());
      }
    }

    // Send payload to Android recipients.
    if (!empty($this->tokens[PUSH_NOTIFICATIONS_TYPE_ID_ANDROID])) {
      try {
        $broadcaster_gcm = \Drupal::service('push_notifications.broadcaster_gcm');
        $broadcaster_gcm->setTokens($this->tokens[PUSH_NOTIFICATIONS_TYPE_ID_ANDROID]);
        $broadcaster_gcm->setMessage($this->message);
        $results = $broadcaster_gcm->getResults();
        // TODO: Log result message.
      } catch (\Exception $e) {
        drupal_set_message(t('Your message could not be sent. Please check the log for details.'), 'error');
        \Drupal::logger('push_notifications')->error($e->getMessage());
      }
    }
  }

  /*
   * Setter function for payload.
   *
   * @param mixed $tokens
   */
  public function setTokens($tokens) {
    $this->tokens = $this->groupTokensByType($tokens);
  }

  /**
   * Setter method for message.
   *
   * @param mixed $message
   */
  public function setMessage($message) {
    $this->message = $message;
  }

  /**
   * Group tokens by type.
   *
   * @param array $tokens_flat Array of token record objects.
   * @return array $tokens Array of tokens grouped by type.
   */
  private function groupTokensByType($tokens_flat = array()) {
    $tokens = array();
    foreach ($tokens_flat as $token) {
      switch ($token->type) {
        case PUSH_NOTIFICATIONS_TYPE_ID_IOS:
          $tokens[PUSH_NOTIFICATIONS_TYPE_ID_IOS][] = $token->token;
          break;

        case PUSH_NOTIFICATIONS_TYPE_ID_ANDROID:
          $tokens[PUSH_NOTIFICATIONS_TYPE_ID_ANDROID][] = $token->token;
          break;
      }
    }
    return $tokens;
  }

}
