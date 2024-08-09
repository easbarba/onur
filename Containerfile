FROM debian:unstable

MAINTAINER EAS Barbosa <easbarba@outlook.com>
LABEL version=${ONUR_VERSION}
LABEL description="Easily manage multiple FLOSS repositories."

RUN apt-get update && \
        apt-get install -y --no-install-recommends build-essential git meson cmake ca-certificates pkg-config && \
        apt-get clean && \
        rm -rf /var/lib/apt/lists/*

ENV USERNAME easbarba
ENV APP_HOME /home/$USERNAME/app
WORKDIR $APP_HOME

RUN groupadd -r $USERNAME && useradd -r -g $USERNAME -d /home/$USERNAME -m -s /bin/bash $USERNAME
RUN chown -R $USERNAME:$USERNAME /home/$USERNAME

COPY examples examples
COPY ./prepare.bash .
RUN ./prepare.bash

COPY . .

RUN CC=g++ meson setup $APP_HOME/build --wipe --backend ninja
RUN CC=g++ meson compile -C $APP_HOME/build

CMD [ "meson", "test", "-C", "/home/easbarba/app/build" ]
