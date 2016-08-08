<?php

/**
* @file
* Contains \Drupal\push_notifications\TokenInterface.
*/

namespace Drupal\push_notifications;

use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\user\EntityOwnerInterface;

/**
* Provides an interface defining a token entity.
 *
* @ingroup push_notifications
*/
interface PushNotificationsTokenInterface extends ContentEntityInterface {

  /**
   * Returns the entity token.
   *
   * @return string
   *   The token for this entity.
   */
  public function getToken();

  /**
 * Returns the entity network.
 *
 * @return string
 *   The network for this entity.
 */
  public function getNetwork();

  /**
   * Returns the entity's created timestamp.
   *
   * @return string
   *   The created timestamp (Unix) for this entity.
   */
  public function getCreatedTimestamp();

  /**
   * Returns the entity's created time.
   *
   * @param string $type
   *   The format type for this date.
   *
   * @return string
   *   The created time for this entity.
   */
  public function getCreatedTime($type);
}