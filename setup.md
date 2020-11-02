```bash
sudo apt update && sudo apt install apache2 supervisor -y
```

> /etc/supervisor/conf.d/smart_home.conf
```conf
[program:smart_home]
directory=/home/pi/Desktop/py_smart_home       
command=/home/pi/Desktop/py_smart_home/venv/bin/gunicorn -w 9 app:app --timeout 18000
user=pi
autostart=true
autorestart=true
stopasgroup=true
killasgroup=true
stderr_logfile=/var/log/smart_home/app.err.log
stdout_logfile=/var/log/smart_home/app.out.log
```
> /etc/apache2/sites-enabled/000-default.conf
```conf
<VirtualHost *:80>
	ProxyPreserveHost On
	ProxyPass / http://127.0.0.1:8000/
	ProxyPassReverse / http://127.0.0.1:8000/
</VirtualHost>
```

> Append /etc/apache2/apache2.conf
```conf
LoadModule proxy_module modules/mod_proxy.so
LoadModule proxy_http_module modules/mod_proxy_http.so
```

```bash
sudo a2enmod proxy
sudo a2enmod proxy_http
sudo a2enmod proxy_balancer
sudo a2enmod lbmethod_byrequests
sudo systemctl restart apache2
```
