<?php

namespace Drupal\push_notifications\Plugin\Validation\Constraint;

use Drupal\Core\Validation\Plugin\Validation\Constraint\UniqueFieldConstraint;

/**
 * Supports validating the token value of a token entity.
 *
 * @Constraint(
 *   id = "PushNotificationTokenToken",
 *   label = @Translation("Token value in token entity", context = "Validation")
 * )
 */
class PushNotificationsTokenTokenConstraint extends UniqueFieldConstraint {

  public $message = 'A token with the value %value already exists. Use a unique token.';

}
