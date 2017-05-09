# psychic-system
TU Delft IN4342 - Embedded Systems Lab

## Members

[Aniket Dhar](https://github.com/AniketDhar)

[Anirudh Bisht](https://github.com/Xiferof)

[Lars Wijtemans](https://github.com/lars2309)

[Philip Dürnay](https://github.com/phil-due)

[Sergio Soto](https://github.com/bajosoto)

[Vincent Koeten](https://github.com/vincentrk)

## Connecting to things

### Example config
Allows these shorthands:  
`ssh eslab.wijtemans.nl`  
`ssh pi.wijtemans.nl`  
`ssh beagle.wijtemans.nl`  

```
# ~/.ssh/config
Host ce-eslab.ewi.tudelft.nl
    User in4342-11
Host 192.168.0.202
    User root
#	KexAlgorithms +diffie-hellman-group1-sha1
Host bajosoto.ddns.net
    User eslab
Host pi.wijtemans.nl
    User eslab
Host eslab.wijtemans.nl
    Port 4342
    User in4342-11
Host beagle.wijtemans.nl
    User root
    ProxyCommand ssh pi.wijtemans.nl -W %h:%p
```

### Raspberry Pi
`ssh eslab@bajosoto.ddns.net`

`ssh eslab@pi.wijtemans.nl`

ECDSA  
SHA256:yFyWp3rWRR67P3BfKla5+q40zbj7yy6l0z+HjcC/hEk.  
MD5:7e:f8:f0:97:70:b2:5f:50:a7:f2:4f:f5:c3:4c:80:48.

### Lab server
With VPN:  
`ssh in4342-11@ce-eslab.ewi.tudelft.nl`

Without VPN:  
`ssh in4342-11@eslab.wijtemans.nl -p 4342`

ECDSA  
SHA256:WeUuJlApFDlIygSDv0YLKwBnEjuPXYAQPoICZFZF93M.  
MD5:5e:08:26:85:09:d1:9d:cd:2d:48:d7:67:d5:00:51:32.

### Beagle (local)
```
sudo ip addr add 192.168.0.200/24 dev usb0
ssh root@192.168.0.200
```

### Beagle (through Raspberry)
```
ssh eslab@bajosoto.ddns.net
ssh root@192.168.0.202
```
`ssh root@192.168.0.202 -o "ProxyCommand ssh eslab@bajosoto.ddns.net -W %h:%p"`

RSA  
SHA256:fPL5Rn5VMAN+pXzgvgKU+IectZtsAeJJChf/A9Sgu78.  
MD5:22:3b:0d:9b:34:f4:cb:0b:67:37:14:0a:93:a0:ba:d2.
