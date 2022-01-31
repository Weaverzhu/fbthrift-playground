FROM debian:bullseye
WORKDIR /project
# ENV HTTP_PROXY=http://127.0.0.1:10809 HTTPS_PROXY=http://127.0.0.1:10809

COPY . ./

RUN ./scripts/build.sh deps