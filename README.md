## Drupal on Heroku

The repository is a sandbox for trying to run Drupal on Heroku. There are still some issues that need to be resolved:

* **ISSUE**: Drupal requires that its public filesystem is within the Drupal root. Heroku's app filesystem is read-only, so this is not possible. This is primarily a problem because you cannot enable CSS and JS aggregation. That's pretty much a requirement for running Drupal in production since IE only supports 32 stylesheets. This is easily exceeded once you add a handful of modules.

## Setup Notes

### PHP Configuration

`php.ini` - Loaded php configuration. Loads the mbstring exension for better unicode support.

`heroku/mbstring.so` - Precompiled mbstring extension. ([yandod/heroku-libraries](https://github.com/yandod/heroku-libraries))

### Sites Configuration

`sites/site.php` - Points Drupal to the `sites/heroku/` folder when running on _*.herokuapp.com_.

### Utility Class

`heroku/heroku.inc` - Utility class for running in the Heroku environment. Currently a function for parsing the database config from the `DATABASE_URL` environment variable and running an array in Drupal's preferred format.

    array Heroku_Util::parseDatabaseUrl($url == false)

### Settings.php

`sites/heroku/settings.php` - An automatic Drupal configuration sample for running in a Heroku environment.

	// Include the utilty class and setup the database
    require_once(DRUPAL_ROOT . '/heroku/heroku.inc');
	$databases['default']['default'] = Heroku_Util::parseDatabaseUrl();

### AmazonS3 File Storage

Include the [AmazonS3](https://drupal.org/project/amazons3) Drupal module so we can store files.