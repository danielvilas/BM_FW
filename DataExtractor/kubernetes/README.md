# Data Extractor
Kubernetes data to have all the info

# Instalation
Create the GlusterFS volume
```
ssh pi@masterpi sudo mkdir -p /data/brick1/gv_bm_fw
ssh pi@nodepi1 sudo mkdir -p /data/brick1/gv_bm_fw
ssh pi@nodepi2 sudo mkdir -p /data/brick1/gv_bm_fw

ssh pi@masterpi sudo gluster volume create gv_bm_fw replica 3 masterpi.local:/data/brick1/gv_bm_fw nodepi1.local:/data/brick1/gv_bm_fw nodepi2.local:/data/brick1/gv_bm_fw force
ssh pi@masterpi sudo gluster volume start gv_bm_fw
```
Mount the volume and create data structure
```
sudo mkdir -p /mnt/gv_bm_fw
sudo mount -t glusterfs masterpi.local:/gv_bm_fw /mnt/gv_bm_fw
sudo chown 472 /mnt/gv_bm_fw/grafana
sudo mkdir -p /mnt/gv_bm_fw/grafana
sudo mkdir -p /mnt/gv_bm_fw/chronograf
sudo mkdir -p /mnt/gv_bm_fw/influxdb
sudo mkdir -p /mnt/gv_bm_fw/job
```
Check remote volume
```
ssh pi@masterpi sudo ls /data/brick1/gv_bm_fw
```
Create Resources
```
kubectl apply -f 00_namespace.yaml
kubectl apply -f 01_influxdb.yaml
kubectl apply -f 02_chronograf.yaml 
kubectl apply -f 03_grafana.yaml 
```
Wait and see files
```
ls /mnt/gv_bm_fw/grafana
ls /mnt/gv_bm_fw/chronograf
ls /mnt/gv_bm_fw/influxdb

```

# CheatSheet
```
ssh  -p xxx -D 127.0.0.1:2424 user@host
https_proxy=socks5://localhost:2424 kubectl -n bm-fw 
```