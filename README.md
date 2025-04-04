# Preparation

```
sudo yum group install -y development-tools
sudo yum install -y automake autoconf mupdf-devel gtk3-devel
```

# First Build
```
aclocal
autoconf
automake --add-missing
./configure
make
```


# Subsequent Build
```
make distclean
autoreconf --force
./configure
make
```
