FROM alpine:3.20.6

RUN apk update && apk add --no-cache \
	mariadb mariadb-client \
	&& rm -rf /var/cache/apk/*

RUN mkdir -p /run/mysqld /var/lib/mysql /var/log/mysql \
    && chown -R mysql:mysql /run/mysqld /var/lib/mysql /var/log/mysql \
    && chmod 750 /var/lib/mysql /run/mysqld /var/log/mysql

COPY ./conf/mariadb.conf /etc/my.conf.d/mariadb.conf
RUN chmod 644 /etc/my.conf.d/mariadb.conf

COPY ./tools/mariadb-script.sh /usr/local/bin/mariadb-script.sh
RUN chmod +x /usr/local/bin/mariadb-script.sh

EXPOSE 3306

ENTRYPOINT ["mariadb-script.sh"]