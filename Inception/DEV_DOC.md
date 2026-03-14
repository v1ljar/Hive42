# Set up the environment from scratch (prerequisites, configuration files, secrets).
## Prerequisites
    ◦ Alpine Linux Virual Machine
    ◦ Docker and required packages installed

## Configutation files
### Docker Compose
    ◦ A tool for defining and running multi-container applications.
    ◦ Makes it easy to manage services, networks and volumes in a single YAML configuration file.
        - Services (each service identified my name) attributes:
            - container_name: set same as service name
            - build: the location of build files (Dockerfile)
            - image: custom name for the image
            - env_file: specify the name of the environment variables file
            - secrets: specify the secrets container has access
            - healthcheck: command to check container status
            - volumes: specify volume that container has access
            - networks: specify networks that container has access
            - restart: specify the bafaviour of failure
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

### Dockerfile
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
        - datadir: set container data directory
        - socket: set container socket location
        - bind-address: set container bind-address
        - port: set container port

    ◦ WordPress Pool Directives (default name is www.conf):
        - [www]: this is only for the www standalone daemon
        - user: 
        - group: 
        - listen: used to mode connecting mechanism of PHP request from frontend server.
        - pm: child processes type (static/dynamic/ondemand)
        - pm.max_children: the maximum number of child processes
        - pm.min_spare_servers: the number of minimum spare servers
        - pm.max_spare_servers: the number of maximum spare servers
        - clear_env: specify to clear environment variables (yes|no)

    ◦ Nginx:
        - user: specify the user to use
        - events: 
            - worker_connections: 
        - http: 
            - include: 
            - server:
                - listen: 
                - server_name:
                - ssl_protocols: 
                - ssl_certificate: 
                - ssl_certificate_key: 
                - root: 
                - location: 
                    - try_files: 
                - location ~ \.php$:
                    - include: 
                    - fastcgi_pass: 
                    - fastcgi_index: 
                    - fastcgi_split_path_info: 
                    - fastcgi_param SCRIPT_FILENAME: 
                    - fastcgi_param PATH_INFO: 

## Secrets
    ◦ Secrets are stored as textfiles and managed by Docker Compose:
        - In Docker Compose is Secrets section, where each file is added to variable.
        - Each container has Secrets section, where is specified, which secret the container has access to.
        - To use the secret, we can call the variable in the script.

# Build and launch the project using the Makefile and Docker Compose.
    ◦ Run the orchestrated docker-compose file:
        make
    ◦ Stop containers without deleting images:
        make down
    ◦ Start containers without building new images:
        make up
    ◦ Just build docker images:
        make images
    ◦ Remove containers, images and volumes:
        make clean
    ◦ Clean up everything:
        make fclean
    ◦ Clear up everything, build and launch:
        make re

# Use relevant commands to manage the containers and volumes.

# Identify where the project data is stored and how it persists.
