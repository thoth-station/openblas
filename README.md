# OpenBLAS
OpenBLAS s2i

https://www.openblas.net/

## Usage

#### 1. Create the templates
```
oc create -f build-image.json
oc create -f build-job.json
```

#### 2. Create build image
```
oc new-app --template=build-image \
--param=APPLICATION_NAME=build-image-1 \
--param=S2I_IMAGE=registry.access.redhat.com/rhscl/s2i-core-rhel7  \
--param=DOCKER_FILE_PATH=Dockerfile.rhel75
```
The above command creates a tensorflow builder image `APPLICATION_NAME:VERSION` for specific OS.

The values for `S2I_IMAGE` are :
- Fedora26- `registry.fedoraproject.org/f26/s2i-core`
- Fedora27- `registry.fedoraproject.org/f27/s2i-core`
- Fedora28- `registry.fedoraproject.org/f28/s2i-core`
- RHEL7.5- `registry.access.redhat.com/rhscl/s2i-core-rhel7`
- Centos7- `openshift/base-centos7`

The values for `DOCKER_FILE_PATH` are :
- Fedora26- `Dockerfile.fedora26`
- Fedora27- `Dockerfile.fedora27`
- Fedora28- `Dockerfile.fedora28`
- RHEL7.5- `Dockerfile.rhel75`
- Centos7- `Dockerfile.centos7`


*OR*

Import the template `build-image.json` into your namespace from Openshift UI.
And then deploy from UI with appropriate values.

#### 3. Create Tensorflow wheel for CPU using the build image

```
oc new-app --template=build-job  \
--param=APPLICATION_NAME=build-job-1 \
--param=BUILDER_IMAGESTREAM=build-image-1
```
NOTE: `BUILDER_IMAGESTREAM = APPLICATION_NAME:VERSION` from step 2.

*OR*

Import the template `build-job.json` into your namespace from Openshift UI.
And then deploy from UI with appropriate values.
