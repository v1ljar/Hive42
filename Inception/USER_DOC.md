# User Documentation
    ◦ This document describes users what services are provided, how to:
        - start/stop the project
        - access website and administration panel
        - locate and manage credential
        - check that the services are running correctly

---

# Provided services
    ◦ There are 3 main services provided:
        - MariaDB: manages the website database
        - WordPress: website frontend and content management
        - NGINX: web server to host website

    ◦ Docker networks are used for internal communication between containers:
        - Only port 443 is exposed to host

    ◦ Docker volumes are use for persistant data management:
        - MariaDB stores website data (users, posts, comments etc.)
        - WordPress stores frontend data

---

# Start/stop the project
The project uses a Makefile to simplify Docker Compose commands.
    Run the orchestrated docker-compose file:
        `make`
    Stop containers without deleting images:
        `make down`
    Start containers without building new images:
        `make up`
    Just build docker images:
        `make images`
    Remove containers, images and volumes:
        `make clean`
    Clean up everything:
        `make fclean`
    Clear up everything, build and launch:
        `make re`

# Access website and administration panel
When everything has been built, up, running and healthy- user has access to website and administration panel.
    ◦ Check connection in terminal:
        - `curl -I https://vuljas.42.fr --insecure`
    ◦ Alternative way to check connection in terminal:
        - `openssl s_client -connect localhost:443 -servername vuljas.42.fr </dev/null | head -n 20`
    ◦ Access to website in browser:
        - `https://vuljas.42.fr`
    ◦ Access to website login page in browser:
        - `https://vuljas.42.fr/wp-login.php`
    ◦ Access to website administartion panel in browser:
        - `https://vuljas.42.fr/wp-admin`

# Locate and manage credential
**Docker Secrets**
    ◦ Secrets are stored as textfiles and managed by Docker Compose.
        - In the Docker Compose, secrets section defines the secret files.
        - Defined secret file are mounted to the container.
        - Each container specifies which secret it has access to.
        - Scripts inside container can read containers secrets now.

**Environment variables**
    ◦ All project related environment variables are defined in .env file.
        - Docker Compose service has env_file variable
            - If container needs access to environment variables [ env_file: .env ]

# Check that the services are running correctly
**Commands**
    ◦ To check services, use command:
        `docker ps -a`
    ◦ To check service log, use command:
        - `docker logs <container name>`
    ◦ To inspect container, use command:
        - `docker inspect <container name>`
    ◦ To check networks, use command:
        - `docker network ls`
    ◦ To inspect network, use command:
        - `docker network inspect <network name>`
    ◦ To check volumes, use command:
        - `docker network ls`
    ◦ To inspect volumes, use command:
        - `docker network inspect <network name>`
