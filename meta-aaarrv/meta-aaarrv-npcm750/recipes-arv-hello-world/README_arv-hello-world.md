# Build the "arv-hello-world" recipe: bitbake arv-hello-world

## Test the command in the BMC console: 
```
/usr/local/bin/arvhelloworld
Hello, world!

```
## added this recipes into image.
```
# added in local.conf. 
IMAGE_INSTALL_append = " arv-hello-world"

```
## added this recipes into packagegroups
```

# added in recipes-phosphor/packagegroups/packagegroup-obmc-apps.bbappend

RDEPENDS_${PN}-extras_append = " \
     arv-hello-world \
     "
```
