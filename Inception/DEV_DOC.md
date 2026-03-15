# **Developer Documentation**

This document describes how developers can set up, build and manage the Inception project.

---

# **Set up the environment from scratch** (prerequisites, configuration files, secrets).
## Prerequisites
- To work with this project, the following components are required:
    - Alpine Linux Virtual Machine
    - Docker
    - Docker Compose
    - Make

Docker and Docker Compose must be installed and accessible by the user running the project.

## Configuration files
The project uses several configuration files to define the infrastructure and services.

### .env file
    ◦ To store variables used in project:
        - DOMAIN_NAME
        - WORDPRESS_TITLE
        - WORDPRESS_DATABASE_NAME
        - WORDPRESS_DATABASE_HOST
        - WORDPRESS_DATABASE_USER
        - WORDPRESS_ADMIN
        - WORDPRESS_ADMIN_EMAIL
        - WORDPRESS_USER
        - WORDPRESS_USER_EMAIL

### Docker Compose | docker-compose.yml
    ◦ Docker Compose is used to define and orchestrate the multi-container architecture.
    ◦ Makes it easy to manage services, networks and volumes in a single YAML configuration file.
        - Services (each service identified by name) attributes:
            - container_name: specifies the container name
            - build: location of the Dockerfile used to build the image
            - image: custom name for the built image
            - env_file: specify the name of the environment variables file
            - secrets: specify the secrets container has access
            - healthcheck: command to check container status
            - volumes: specify volume that container has access
            - networks: specify networks that container has access
            - restart: restart policy
            - depends_on: specify on which service the container depends on
            - ports: expose the port to host

        - Volumes (each volume identified by name) attributes:
            - name: custom name for the volume
            - driver: specify volume driver name
            - driver_opts:
                - type: Cluster Volume access type
                - o: set driver specific options
                - device: specify volume location on host

        - Networks (each network identified by name) attributes:
            - name: set custom name for network
            - drivers: specify the network driver

        - Secrets (each secret identified by name) attributes:
            - file: location of secret file

### Dockerfiles
    ◦ Each container has Dockerfile that is a text document that contains all the commands a user could call on the command line to assemble an image. Used instructions:
        - FROM: initializes a new build stage and sets the base image for subsequent instructions.
        - RUN: will execute any commands to create a new layer on top of the current image.
        - COPY: copies files from the build context.
        - EXPOSE: informs Docker that the container listens on the specified network ports at runtime.
        - ENTRYPOINT: allows you to configure a container that will run as an executable.
        - CMD: sets the command to be executed when running a container from an image.

### .dockerignore file
    ◦ Use .dockerignore file to exclude files and directories from the build context.

### Container specific .conf file
    ◦ MariaDB:
        - [mysqld]: this is only for the mysqld standalone daemon
        - datadir: database data directory
        - socket: socket file location
        - bind-address: set container bind-address
        - port: set container port

    ◦ WordPress Pool Directives (default name is www.conf):
        - [www]: this is only for the www standalone daemon
        - user: process user
        - group: process group
        - listen: socket or port used by PHP-FPM
        - pm: process manager mode
        - pm.max_children: the maximum number of child processes
        - pm.min_spare_servers: the number of minimum spare servers
        - pm.max_spare_servers: the number of maximum spare servers
        - clear_env: specify to clear environment variables (yes|no)

    ◦ Nginx:
        - user: worker process user
        - events: events block contains settings for server
            - worker_connections: set how many connections a worker can open
        - http: http block specifies global configuration settings for the NGINX HTTP server
            - include: specify to include conf file
            - server: server block contains settings for a specific server
                - listen: specifies the port to listen for incoming connections
                - server_name: specifies the domain name that this server block should handle
                - ssl_protocols: specify protocols to use
                - ssl_certificate: set certification location
                - ssl_certificate_key: set certification key location
                - root: specify the root directory
                - location /: specifies that requests for the root URL of the website
                    - try_files: set file locations to use
                - location ~ \.php$: location block for ~ \.php$ specifies how the server should handle server errors by serving a specific file
                    - include: specify to include conf file
                    - fastcgi_pass: sets the address of a FastCGI server
                    - fastcgi_index: sets a file name that will be appended after a URI 
                    - fastcgi_split_path_info: a regular expression that captures a value for the $fastcgi_path_info variable
                    - fastcgi_param SCRIPT_FILENAME: sets SCRIPT_FILENAME parameter that should be passed to the FastCGI server
                    - fastcgi_param PATH_INFO: sets PATH_INFO parameter that should be passed to the FastCGI server

### Setup scripts (Mariadb & WordPress)
<p>MariaDB and WordPress need initialization/setup before usage.</p>

- MariaDB:
    ◦ Check if database exists
        - If NOT exist:
            - Initialize datadirectory
            - Use bootstrap to setup database
        - Make sure MariaDB configuration file:
            - Is not skipping networking
            - Bind address is 0.0.0.0
        - Start the mariadb

- WordPress:
    ◦ Check WP-CLI exists:
        - If NOT exist:
            - Download it with wget & give execution permission
    ◦ Check if MariaDB is running:
        - If NOT running:
            - Wait for it!
    ◦ Check if WordPress is downloaded:
        - If NOT:
            - Download it with `core download`
            - Create configuration with `config create`
            - Install WordPress with `core install`
            - Create WordPress user with `user create`
        - Make sure directories have right permissions and ownership
        - Execute PHP-FPM in the foreground

## Secrets
    ◦ Secrets are stored as textfiles and managed by Docker Compose:
        - In Docker Compose is Secrets section, where each file is added to variable.
        - Each container has Secrets section, where is specified, which secret the container has access to.
        - To use the secret, we can call the variable in the script.

---

# **Build and launch the project using the Makefile and Docker Compose.**
## The project uses a Makefile to simplify Docker Compose commands.
    ◦ Run the orchestrated docker-compose file:
        - `make`
    ◦ Stop containers without deleting images:
        - `make down`
    ◦ Start containers without building new images:
        - `make up`
    ◦ Just build docker images:
        - `make images`
    ◦ Remove containers, images and volumes:
        - `make clean`
    ◦ Clean up everything:
        - `make fclean`
    ◦ Clear up everything, build and launch:
        - `make re`

---

# **Use relevant commands to manage the containers and volumes.**
    ◦ Show all containers:
        `docker ps -a`
    ◦ Show disk usage by container:
        `docker ps --size`
    ◦ Display detailed information on one or more containers:
        `docker container inspect <container name>`
    ◦ Fetch the logs of a container:
        `docker logs <container name>`
    ◦ Lists all the networks the Engine daemon knows about:
        `docker network ls`
    ◦ Returns information about one or more networks:
        `docker network inspect <network name>`

---

# **Identify where the project data is stored and how it persists.**
- The project uses Docker volumes to ensure data persists between container restarts or recreations.
## Data storage locations:
    - Inside containers:
        ◦ MariaDB: /var/lib/mysql
        ◦ WordPress: /var/www/html
    - On the host system:
        ◦ /home/viljar/data/
    - Loggin to wordpress in browser:
        ◦ https://vuljas.42.fr/wp-login.php
    - Loggin to wordpress administrator panel in browser:
        ◦ https://vuljas.42.fr/wp-admin

## Useful commands:
    - Access MariaDB container:
        ◦ `docker exec -it mariadb sh`
    - Show list of volumes:
        ◦ `docker volume ls`
    - To inspect the configuration of the volume:
        ◦ `docker volume inspect <volume name>`
    - Access MariaDB database:
        ◦ `docker exec -it mariadb mariadb -u root -p`
            - To see databases:
                ◦ `SHOW DATABASES;`
            - Choose "wordpress" database:
                ◦ `USE WORDPRESS;`
            - Show tables:
                ◦ `SHOW TABLES;`
            - To see comments:
                ◦ `SELECT comment_content FROM wp_comments;`
