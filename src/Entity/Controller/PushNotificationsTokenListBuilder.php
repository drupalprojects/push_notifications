<?php

/**
 * @file
 *
 * Contains Drupal\push_notifications\Entity\Controller\PushNotificationsTokenListBuilder.
 */

namespace Drupal\push_notifications\Entity\Controller;

use Drupal\Core\Entity\EntityInterface;
use Drupal\Core\Entity\EntityListBuilder;
use Drupal\user\Entity\User;

/**
 * Provides a list controller for push_notifications_token entity.
 *
 * @ingroup push_notifications_token
 */
class PushNotificationsTokenListBuilder extends EntityListBuilder {

  /**
   * {@inheritdoc}
   *
   * We override ::render() so that we can add our own content above the table.
   * The token analytics part
   */
  public function render() {
    $build['description'] = array(
      // @TODO: modify this markup
      '#markup' => $this->t('Here is a list of all the tokens in the database.'),
    );

    $build['table'] = parent::render();
    $build['table']['table']['#empty'] = $this->t('There are no device tokens registered yet.');

    return $build;
  }

  /**
   * {@inheritdoc}
   */
  public function buildHeader() {
    $header['id'] = $this->t('ID');
    $header['uid'] = $this->t('Token owner');
    $header['token'] = $this->t('Device Token');
    $header['network'] = $this->t('Network');
    $header['created'] = $this->t('Created');

    return $header + parent::buildHeader();
  }

  /**
   * {@inheritdoc}
   */
  public function buildRow(EntityInterface $entity) {
    /* @var $entity \Drupal\push_notifications\Entity\PushNotificationsToken */

    $row['id'] = $entity->id();
    // @TODO: Maybe here it will be alright if we link the user to his page
    $row['uid'] = $entity->getOwner()->getDisplayName();
    $row['token'] = $entity->token->value;
    $row['network'] = $entity->network->value;
    $row['created'] = \Drupal::service('date.formatter')->format($entity->timestamp->value, 'short');

    return $row + parent::buildRow($entity);
  }

}