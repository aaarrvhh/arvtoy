# Build the "arv-hello-world" module: bitbake arv-hello-world

## Test the command in the BMC console: 
```
/usr/local/bin/arvhelloworld
Hello, world!

```
## added this recipes into image.
```
added in local.conf. 
i have no idea for adding this into packagegroups.

IMAGE_INSTALL_append = " arv-hello-world"

```

