<?php

/**
 * A collection of utlity functions for Drupal in the Heroku environment
 */
class Heroku_Util {

	/**
	 * Parse the database connection from the environment and return a config array of the form
	 *   $databases['default']['default'] = array(
	 *     'driver' => 'mysql',
	 *     'database' => 'databasename',
	 *     'username' => 'username',
	 *     'password' => 'password',
	 *     'host' => 'localhost',
	 *     'prefix' => '',
	 *   );
	 */
	public static function parseDatabaseUrl($url = false) {
		if (empty($url)) {
			$url = $_ENV['DATABASE_URL'];
		} else {
			throw new RuntimeException('Environment variable DATABASE_URL missing.');
		}

		$db = parse_url($url);

		$config = array();
		if ($db['scheme'] == 'postgres') {
			$config['driver'] = 'pgsql';
		} else {
			throw new RuntimeException('Unknown database scheme: ' . $db['scheme']);
		}
		$config['database'] = $db['path'];
		$config['username'] = $db['user'];
		$config['password'] = $db['pass'];
		$config['host'] = $db['host'];
		if (isset($db['port'])) {
			$config['port'] = $db['port'];
		}

		return array('default' => array('default' => $config));
	}
}
