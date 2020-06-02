iptables -I INPUT -p tcp –-dport 5000 -j REJECT
service iptables save