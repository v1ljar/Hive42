#!/bin/sh
set -e

MYSQL_DATADIR="/var/lib/mysql"
MYSQL_SOCKET="/run/mysqld/mysqld.sock"
WORDPRESS_DATABASE_USER_PASSWORD=$(tr -d '\r\n' < /run/secrets/db_password)


# Initialize system tables if they don't exist
if [ ! -d "$MYSQL_DATADIR/mysql" ]; then
    echo "[MariaDB] Initializing datadir..."

    mariadb-install-db \
        --user=mysql \
        --basedir=/usr \
        --datadir="$MYSQL_DATADIR"

    echo "[MariaDB] Running bootstrap SQL..."
    mariadbd \
        --user=mysql \
        --bootstrap \
        --datadir="$MYSQL_DATADIR" <<EOF

USE mysql;
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS \`${WORDPRESS_DATABASE_NAME}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER IF NOT EXISTS '${WORDPRESS_DATABASE_USER}'@'%' IDENTIFIED BY '${WORDPRESS_DATABASE_USER_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${WORDPRESS_DATABASE_NAME}\`.* TO '${WORDPRESS_DATABASE_USER}'@'%';
FLUSH PRIVILEGES;
EOF

    echo "[MariaDB] Initialization complete."
else
    echo "[MariaDB] Database already initialized."
fi

echo "[MariaDB] Starting main server..."
exec mariadbd-safe --defaults-file=/etc/my.cnf.d/mariadb_config.cnf
