<?php

/**
* @file
* Contains \Drupal\push_notifications\TokenInterface.
*/

namespace Drupal\push_notifications;

use Drupal\Core\Entity\ContentEntityInterface;
#use Drupal\Core\Entity\EntityChangedInterface;
#use Drupal\user\EntityOwnerInterface;

/**
* Provides an interface defining a token entity.
 *
* @ingroup push_notifications
*/
interface PushNotificationsTokenInterface extends ContentEntityInterface {
  // Extend push notifications token interface with more functionality.
}