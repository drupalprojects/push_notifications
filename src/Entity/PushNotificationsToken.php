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
 *   admin_permission = "administer device tokens",
 *   fieldable = FALSE,
 *   handlers = {
 *     "storage_schema" = "Drupal\push_notifications\PushNotificationsTokenStorageSchema",
 *     "list_builder" = "Drupal\push_notifications\Entity\Controller\PushNotificationsTokenListBuilder",
 *   },
 *   entity_keys = {
 *     "id" = "id",
 *     "uuid" = "uuid",
 *     "label" = "token",
 *   },
 * )
 */
class PushNotificationsToken extends ContentEntityBase implements PushNotificationsTokenInterface {

  /**
   * {@inheritdoc}
   */
  public function getOwner() {
    return $this->get('uid')->entity;
  }

  /**
   * {@inheritdoc}
   */
  public function getOwnerId() {
    return $this->get('uid')->target_id;
  }

  /**
   * {@inheritdoc}
   */
  public function getToken() {
    return $this->get('token')->value;
  }

  /**
   * {@inheritdoc}
   */
  public function getNetwork() {
    return $this->get('network')->value;
  }

  /**
   * {@inheritdoc}
   */
  public function getCreatedTimestamp() {
    return $this->get('created')->value;
  }

  /**
   * {@inheritdoc}
   */
  public function getCreatedTime($type = 'short') {
    return \Drupal::service('date.formatter')->format($this->getCreatedTimestamp(), $type);
  }

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

    // User ID.
    $fields['uid'] = BaseFieldDefinition::create('entity_reference')
      ->setLabel(t('User Name'))
      ->setDescription(t('The token owner.'))
      ->setSetting('target_type', 'user')
      ->setDefaultValue(0);

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
    $fields['created'] = BaseFieldDefinition::create('timestamp')
      ->setLabel(t('Created Timestamp'))
      ->setDescription(t('Timestamp the token was created.'))
      ->setRequired(TRUE);

    return $fields;
  }
}
