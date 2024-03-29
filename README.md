# psychic-system
TU Delft IN4342 - Embedded Systems Lab

## Members

[Aniket Dhar](https://github.com/AniketDhar)

[Anirudh Bisht](https://github.com/Xiferof)

[Lars Wijtemans](https://github.com/lars2309)

[Philip Dürnay](https://github.com/phil-due)

[Sergio Soto](https://github.com/bajosoto)

[Vincent Koeten](https://github.com/vincentrk)

## Link to Overleaf
[REPORT ASSIGNMENT 02](https://www.overleaf.com/9529805tfmgpcsshcry)

[PRESENTATION ASSIGNMENT 02](https://www.overleaf.com/9928537yyvcjcjjfjcp)
## Git
Please set your e-mail address when you clone the repo to the server.  
`git config user.email mygitemail@example.com`

## Connecting to things

### Example config
Allows these shorthands:  
`ssh eslab.wijtemans.nl`  
`ssh pi.wijtemans.nl`  
`ssh beagle.wijtemans.nl`  

These commands are already enabled on the eslab server, so you can ssh/scp directly to the board from the server.
(Note: eslab server blocks outgoing connections to ssh port.)

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
SHA256:77D0X4tz8inuztflcTBKTnTgEVFmii4zyL4yulPbAyk.  
MD5:c2:25:09:79:f8:7c:9b:1f:0e:ca:47:52:71:0a:fd:8e.

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
