<?php

/**
 * @file
 * Contains \Drupal\push_notifications\Entity\PushNotificationsToken.
 */

namespace Drupal\push_notifications\Entity;

use Drupal\push_notifications\PushNotificationsTokenInterface;
use Drupal\Core\Entity\ContentEntityBase;
use Drupal\Core\Field\BaseFieldDefinition;
use Drupal\Core\Entity\EntityTypeInterface;

/**
 * Defines the token entity.
 *
 * @ContentEntityType(
 *   id = "push_notifications_token",
 *   label = @Translation("Push Notifications Token"),
 *   base_table = "push_notifications_tokens",
 *   handlers = {
 *     "storage_schema" = "Drupal\push_notifications\PushNotificationsTokenStorageSchema",
 *   },
 *   entity_keys = {
 *     "id" = "id",
 *     "uuid" = "uuid",
 *   },
 * )
 */
class PushNotificationsToken extends ContentEntityBase implements PushNotificationsTokenInterface {

  public static function baseFieldDefinitions(EntityTypeInterface $entity_type) {
    // Standard field, used as unique if primary key.
    $fields['id'] = BaseFieldDefinition::create('integer')
      ->setLabel(t('ID'))
      ->setDescription(t('Push notifications ID.'))
      ->setReadOnly(TRUE);

    // UUID field.
    $fields['uuid'] = BaseFieldDefinition::create('uuid')
      ->setLabel(t('UUID'))
      ->setDescription(t('The UUID of the push notifications token.'))
      ->setReadOnly(TRUE);

    // Token.
    $fields['token'] = BaseFieldDefinition::create('string')
      ->setLabel(t('Token'))
      ->setDescription(t('Device Token'))
      ->setRequired(TRUE)
      ->setSettings(array(
        'max_length' => 255,
      ));

    // Network.
    $fields['network'] = BaseFieldDefinition::create('string')
      ->setLabel(t('Network'))
      ->setDescription(t('Network Type'))
      ->setRequired(TRUE)
      ->setSettings(array(
        'max_length' => 255,
      ));

    // Timestamp.
    $fields['timestamp'] = BaseFieldDefinition::create('timestamp')
      ->setLabel(t('Timestamp'))
      ->setDescription(t('Timestamp the token was added.'))
      ->setRequired(TRUE);

    return $fields;
  }
}
