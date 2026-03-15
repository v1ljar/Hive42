*This project has been created as part of the 42 curriculum by vuljas.*

---

# Description
	The goal of the Inception project is to build a small containerized web infrastructure using Docker.
	Project is done inside a Virtual Machine, where three containers are orchestrated using Docker Compose to run a blogging webpage.
	Three main services:
		◦ MariaDB - database used by WordPress
		◦ WordPress - content management system (CMS) based on PHP and MySQL
		◦ Nginx - web server handling HTTPS connections

	Each service runs in its own container, communicates through Docker network and data is stored using Docker volumes.

	The project also includes documentation files (README.md, DEV_DOC.md, USER_DOC.md) that describe the architecture, development process and instructions for managing the containers.

---

# Instructions
### Virtual Machine Setup
	◦ This project was done in VM and I chose alpine-standard-3.23.3-x86_64 ISO image to set up the VM with Oracle VirtualBox.
	◦ To create a new VM, in Oracle VirtualBox click on New, then fill the fields:
		- Name: Alpine Linux [ the name of VM ]
		- Folder: S:\ [ VM files destination ]
		- ISO Image: C:\alpine-standard-3.23.3-x86_64.iso [ base image of VM ]
		- Base Memory: 2048 [ specify the amount of RAM for VM ]
		- Processors: 2 [ specify the amount of CPUs for VM ]
		- Hard Disk Size: 15.00GB [ specify the size of memory for VM ]
		- Click Next, it shows the overview, click Finish.

	◦ Right-Click on VM name in Oracle, choose Settings.
		- Display tab and put the display memory to max (128 MB).
		- Click OK to save the settings.

### Alpine Linux Installation
	◦ Start the VM by double-clicking on its name. [ Alpine installation is text-based ]
	◦ When the machine starts, you will be prompted to log in. Just type root and enter.
	◦ To start the installer, enter: setup-alpine
	◦ You need to select the keyboard layout. Here, I have chosen “us”.
	◦ Enter a hostname of your choice. The default was localhost.
	◦ Enter the network interface selection. I press Enter to select default.
	◦ It now asks to set the IP. I press Enter to select default.
	◦ It asks you if you want to continue manual network configuration? n
	◦ Set up root password and retype it.
	◦ Select the timezone. Europe\ Helsinki
	◦ HTTP proxy settings? I press Enter to select default.
	◦ Select which NTP client to run. I press Enter to select default.
	◦ Enter mirror number or URL: f
	◦ Set up a new user and password.
	◦ Set up SSH related settings. I press Enter to select default.
	◦ Select disk to use. sda
	◦ It asks you to enter How to use it? sys
	◦ It asks to erase the disk and continue? y
	◦ Power off the VM, execute command poweroff

	Open the VM Settings -> Storage -> Controller:IDE -> Erase the ISO image

### Desktop Environment Setup
	◦ Start the VM again [ to set up a minimal Xfce desktop and LightDM display manager ]
	◦ To edit textfiles, we install nano: apk nano
	◦ Make sure that the default user is added to wheel group : adduser <username> wheel
	◦ Make sure the wheel group has its privileges /etc/doas.d/doas.conf [permit persist :wheel]
	◦ Enable community repositories: nano /etc/apk/repositories -> Uncomment line */community
	◦ Make sure that you have xorg-base set up: setup-xorg-base
	◦ Install the Xfce and related packages
		- apk add xfce4 xfce4-terminal xfce4-screensaver lightdm-gtk-greeter dbus
	◦ Start the dbus (desktop bus) service: rc-service dbus start
	◦ Enable dbus to start on boot: rc-update add dbus
	◦ Enable udev service: setup-devd udev
	◦ Now start the LightDM using: rc-service lightdm start
	◦ LightDM GUI starts -> Log in as root -> Open terminal
	◦ Make lightdm to start on boot: rc-update add lightdm
	◦ Allow Users to shut down and reboot: apk add elogind polkit-elogind
	◦ Now, poweroff the system: poweroff

### SSH Setup
	◦ Open VM settings -> Network -> Port Forwarding:
		- Name: SSH | Protocol: TCP | Host Port: 3022 | Guest Port: 22
	◦ Start the VM.
		- Install the OpenSSH package: apk add openssh
		- Enable the sshd service to get started at boot time: rc-update add sshd
		- Start the sshd service on Alpine Linux: service sshd start
		- Now you can SSH from host machine: ssh <user>@localhost -p 3022

### Docker Installation
	◦ Install Docker and Docker Compose v2:
	◦ doas apk add docker docker-cli-compose
	◦ Allow Docker access for your user: addgroup <USER> docker

### Configure Domain Name
	◦ Configure domain name so it points to the local IP address:
		- echo "127.0.0.1 vuljas.42.fr" >> /etc/hosts

### Project Structure
	◦ Install doas (so user can call "sudo" commands): apk add doas
	◦ Reboot VM and log in to the user account.
	◦ Create project repository: mkdir Inception
	◦ Create required files:
		cd Inception
		.
		├── Makefile
		├── secrets
		│   ├── credentials.txt
		│   ├── db_password.txt
		│   └── db_root_password.txt
		└── srcs
			├── .env
			├── docker-compose.yml
			└── requirements
				├── mariadb
				│   ├── Dockerfile
				│   ├── conf
				│   │   └── mariadb.conf
				│   └── tools
				│       └── mariadb-script.sh
				├── nginx
				│   ├── Dockerfile
				│   └── conf
				│       └── nginx.conf
				└── wordpress
					├── Dockerfile
					├── conf
					│   └── www.conf
					└── tools
						└── wordpress-script.sh

### Execution
	◦ Run the orchestrated docker-compose file: make
	◦ Stop containers without deleting images: make down
	◦ Start containers without building new images: make up
	◦ Just build docker images: make images
	◦ Remove containers, images and volumes: make clean
	◦ Clean up everything: make fclean
	◦ Clear up everything, build and launch: make re

---

# Resources
 ◦ [Alpine Linux setup guide](https://itsfoss.com/alpine-linux-virtualbox/)
 ◦ [SSH connection setup](https://www.geeksforgeeks.org/installation-guide/how-to-install-openssh-on-alpine/)
 ◦ [VirtualBox shared folders](https://wiki.alpinelinux.org/wiki/VirtualBox_shared_folders)
 ◦ [Install Docker and Docker Compose](https://virtualzone.de/posts/alpine-docker-rootless/)
 ◦ [Docker Compose](https://docs.docker.com/compose/intro/compose-application-model/)
 ◦ [Dockerfile](https://docs.docker.com/build/concepts/dockerfile/)
 ◦ [Dockerfile Best Practices](https://docs.docker.com/build/building/best-practices/)
 ◦ [Mariadb](https://hub.docker.com/_/mariadb)
 ◦ [Wordpress](https://hub.docker.com/_/wordpress)
 ◦ [Nginx](https://hub.docker.com/_/nginx)
 ◦ [Wordpress with docker compose](https://www.linode.com/docs/guides/wordpress-with-docker-compose/)
 ◦ [Explaining Docker Networking Concepts](https://ostechnix.com/explaining-docker-networking-concepts/)
 ◦ [WordPress Deployment with NGINX, PHP-FPM and MariaDB using Docker Compose](https://medium.com/swlh/wordpress-deployment-with-nginx-php-fpm-and-mariadb-using-docker-compose-55f59e5c1a)
 ◦ [Virtual Machines vs Docker](https://www.geeksforgeeks.org/devops/difference-between-docker-and-virtualization/)
 ◦ [Secrets](https://docs.docker.com/engine/swarm/secrets/)
 ◦ [Secrets Handling](https://medium.com/@jagadeeshkema/docker-secrets-environment-variables-handling-sensitive-data-the-right-way-0eacb628b7d9)
 ◦ [Docker Networks](https://bunny.net/academy/computing/what-is-docker-networking/)

	◦ AI usage:
		- AI (ChatGPT) was used to explain different concepts, so I would understand them better.
		- Ask questions related to the project so I can express my understanding of the project and if needed, also detect flaws in knowledge and fix them.
		- I ran into problems with docker-compose, tried to find out the cause of the problem also by sharing the problem with AI, but AI was rather useless in that case.

---

# Project description
### Design Choices
	◦ Alpine Linux was chosen as the base system because it is lightweight and minimal.
	◦ Docker Compose was used to orchestrate multiple containers and manage networking, volumes and dependencies between services.
	◦ MariaDB was used as the database backend, to store website data.
	◦ WordPress was used as the frontend, the content of the website.
	◦ Nginx was used as the web server.
	◦ Docker Volumes were used to ensure persistent storage of database data and WordPress files even when recreating containers.

### Virtual Machines vs Docker
						DOCKER								|					VIRTUAL MACHINE
	◦ It boots in a few seconds.							|	◦ It takes a few minutes for VMs to boot.
	◦ Pre-built docker containers are readily available.	|	◦ Ready-made VMs are challenging to find.
	◦ Docker has a complex usage mechanism consisting		|	◦ Tools are easy to use and more straightforward to 
		of both third-party and docker-managed tools.		|		work with. third-party.
	◦ Limited to Linux.										|	◦ Can run a variety of guest OS.
	◦ Dockers make use of the execution engine.				|	◦ VMs make use of the hypervisor.
	◦ It is lightweight.									|	◦ It is heavyweight.
	◦ Host OS can be different from container OS.			|	◦ Host OS can be different from guest OS.
	◦ Can run many docker containers on a laptop.			|	◦ Cannot run more than a couple of VMS on laptop
	◦ Docker can get a virtual network adapter. It can have	|	◦ Each VMS gets its virtual network adapter.
		separate IPs ad Ports.								|
	◦ Sharing of files is possible.							|	◦ Sharing library and files are not possible.
	◦ Lacks security measures.								|	◦ Security depends on the hypervisor.
	◦ A container is portable.								|	◦ VMS is dependent on a hypervisor.
	◦ It allows running an application in an isolated		|	◦ It provides easiness in managing applications, 
		environment known as a container					|		recovery mechanisms, and isolation from the host
															|		operating system.

### Secrets vs Environment Variables
					ENVIRONMENT VARIABLES					|					SECRETS
	◦ Visible via docker inspect							|	◦ Stored securely by Docker
	◦ Visible in process lists								|	◦ Mounted as files
	◦ Logged accidentally in apps							|	◦ Not visible in image or logs
	◦ Environment Variables are not encrypted				|	◦ Avoid exposing sensitive data

### Docker Network vs Host Network
	◦ Docker Network - the bridge network is the default mode in Docker.
	A bridge network is a private internal network that allows containers on the same host to communicate. How it works:
		- The Docker daemon creates a virtual bridge (e.g., docker0) on the host.
		- Each container is assigned a virtual Ethernet interface (veth) that connects to the bridge.
		- Containers can communicate with each other via their assigned IPs on the bridge network.
		- The bridge uses Network Address Translation (NAT) to allow external communication.

	◦ Host Network
		- Host networking removes network isolation and allows a container to share the host’s network stack.
		- Improves performance but reduces security and flexibility.
		- Additionally, the container does not receive a separate IP address and instead shares the host’s IP.
		- This networking method is useful for performance-sensitive applications but is not ideal for applications requiring isolation.

### Docker Volumes vs Bind Mounts
	Docker volume and Bind mount are the docker components. Using bind mounts, you may mount a file or directory from your host computer onto your container and access it using its absolute path. Because Docker does everything independently, it is not dependent on the host computer's operating system or your directory structure. The Docker CLI commands or the Docker API may be used to manage Docker Volumes. It is safer to share quantities among many containers. The host computer's absolute path to the file or directory serves as a point of reference. Conversely, when a volume is used, Docker makes a new directory in the host machine's storage directory and keeps it updated.

						DOCKER VOLUMES						|					BIND MOUNTS
	◦ Docker volume is the recommended method for storing	|	◦ Bind mount has existed from Docker's early versions
		data created and utilized by Docker containers is	|		Comparatively speaking, bind mounts are less useful
		to use volumes.										|		than volumes.
	◦ Docker volumes may be interacted with using CLIs		|	◦ Bind mounts cannot be accessed by CLI commands. May
		and APIs.											|		still work instantly with them on the host system.
	◦ All you need is the volume name to mount it.			|	◦ When using bind mounts for mounting, a route to the 
															|		host computer must be supplied. 
	◦ In /var/lib/docker/volumes, the volumes are stored.	|	◦ On the host, a bind mount can be located anywhere.
