FROM debian:unstable

MAINTAINER EAS Barbosa <easbarba@outlook.com>
LABEL version=${ONUR_VERSION}
LABEL description="Easily manage multiple FLOSS repositories."

RUN apt-get update && \
        apt-get install -y --no-install-recommends build-essential git meson cmake ca-certificates && \
        apt-get clean && \
        rm -rf /var/lib/apt/lists/*

ENV NEWUSER easbarba
ENV APP_HOME /home/$USER_NAME/app
ENV PATH "/home/$NEWUSER/.local/bin:$PATH"
RUN useradd -ms /bin/bash $NEWUSER && mkdir $APP_HOME && chown -R $USER_NAME:$USER_NAME $APP_HOME
USER $NEWUSER
WORKDIR $APP_HOME

COPY ./prepare.bash .
RUN ./prepare.bash

COPY . .

RUN CC=g++ meson setup $APP_HOME/build --wipe --backend ninja
RUN CC=g++ meson compile -C $APP_HOME/build

CMD [ "meson", "test", "-C", $APP_HOME/build ]
