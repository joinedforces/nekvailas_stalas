<?php

require_once __DIR__ . '/../vendor/autoload.php';

$app = new \Silex\Application();

require_once __DIR__ . '/../src/app.php';

$app->run();
