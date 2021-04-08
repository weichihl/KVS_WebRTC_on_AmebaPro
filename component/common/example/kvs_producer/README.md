# Setup and build code

### Setup AmebaPro SDK

```
git clone git@github.com:weichihl/ambpro_sdk.git --recursive
cd ambpro_sdk
```

### Setup KVS producer embedded C SDK 

KVS producer embedded C SDk is private repository.  It would be a little tricky to make it as git submodule, so we didn't put it in submodule.
We setup it by cloning it as following:

```
cd lib_amazon
git clone -b v0.0.1 git@github.com:iotlabtpe/amazon-kinesis-video-streams-producer-embedded-c.git --recursive
cd amazon-kinesis-video-streams-producer-embedded-c/libraries/aws/coreHTTP
git apply ../../../patch/0001-coreHTTP.patch
```

### Configure example

We need to enable CONFIG_EXAMPLE_KVS_PRODUCER in `platform_opts.h`.

And then configure `example_kvs_producer.h`.

Now we can build and verify it.