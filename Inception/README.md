This project has been created as part of the 42 curriculum by vuljas.

Description [ section that clearly presents the project, including its goal and a
brief overview ]
The goal of the project Inception is to set up an architecture in Virtual Machine that is able to host
and manage a blog website by using Docker containers, networks and volumes. Project also requires
documents as README.md, DEV_DOC.md and USER.md, that should reflect how the project was made and how to
use the Docker.

Instructions [ section containing any relevant information about compilation,
installation, and/or execution ]
This project was done in virtual machine and I chose alpine-standard-3.23.3-x86_64 ISO image to set up
the virtual machine with Oracle VirtualBox.
I followed the setup instructions: "Alpine Linux setup guide" => Virtual Machine Alpine Linux with Graphical Interface.
For SSH connection I followed "SSH connection setup" guide.
I installed firefox, set up shared folder with host, set up VS Code extencion "REMOTE-SSH" (so I can code, access
and manage files in VM easily).

Resources [ section listing classic references related to the topic (documentation,
articles, tutorials, etc.), as well as a description of how AI was used —
specifying for which tasks and which parts of the project ]
"Alpine Linux setup guide" [https://itsfoss.com/alpine-linux-virtualbox/]
"SSH connection setup" [https://www.geeksforgeeks.org/installation-guide/how-to-install-openssh-on-alpine/]

A Project description [ section must also explain the use of Docker and the sources
included in the project. It must indicate the main design choices, as well as a
comparison between:
	◦ Virtual Machines vs Docker
	◦ Secrets vs Environment Variables
	◦ Docker Network vs Host Network
	◦ Docker Volumes vs Bind Mounts ]