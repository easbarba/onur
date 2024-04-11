FROM debian:unstable-slim
WORKDIR /app
COPY . .
RUN ./prepare.bash
CMD [ "test" ]
