# Start from the code-server Debian base image
FROM codercom/code-server:3.12.0

USER coder

# Apply VS Code settings
COPY deploy-container/settings.json .local/share/code-server/User/settings.json

# Use bash shell
ENV SHELL=/bin/bash

# Install unzip + rclone (support for remote filesystem)
RUN sudo apt-get update && sudo apt-get install unzip -y
RUN curl https://rclone.org/install.sh | sudo bash

# Copy rclone tasks to /tmp, to potentially be used
COPY deploy-container/rclone-tasks.json /tmp/rclone-tasks.json

# Fix permissions for code-server
RUN sudo chown -R coder:coder /home/coder/.local

# You can add custom software and dependencies for your environment below
# -----------
RUN sudo apt-get install -y nodejs
RUN sudo apt-get install -y build-essential
RUN sudo apt-get install -y wget 
RUN sudo apt-get -y install cmake
RUN sudo apt-get install -y build-essential
                
RUN code-server --install-extension esbenp.prettier-vscode

RUN code-server --install-extension twxs.cmake 
RUN code-server --install-extension ms-vscode.cmake-tools 
RUN code-server --install-extension ms-python.python 
RUN code-server --install-extension mhutchie.git-graph
RUN code-server --install-extension christian-kohler.path-intellisense
RUN wget https://github.com/microsoft/vscode-cpptools/releases/download/1.6.0/cpptools-linux.vsix

RUN sudo apt-get update
RUN sudo apt-get install -y python3 python3-venv python3-pip
RUN sudo apt-get install -y python3-numpy
RUN sudo apt-get install -y python3-pip
RUN sudo apt-get install -y python3-matplotlib

# Install a VS Code extension:
# Note: we use a different marketplace than VS Code. See https://github.com/cdr/code-server/blob/main/docs/FAQ.md#differences-compared-to-vs-code
# RUN code-server --install-extension esbenp.prettier-vscode

# Install apt packages:
# RUN sudo apt-get install -y ubuntu-make

# Copy files: 
# COPY deploy-container/myTool /home/coder/myTool

# -----------

RUN code-server --install-extension cpptools-linux.vsix 
# Port
ENV PORT=8080

# Use our custom entrypoint script first
COPY deploy-container/entrypoint.sh /usr/bin/deploy-container-entrypoint.sh
ENTRYPOINT ["/usr/bin/deploy-container-entrypoint.sh"]
