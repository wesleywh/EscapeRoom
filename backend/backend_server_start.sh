# iptables -I INPUT -p tcp --dport 5000 --syn -j ACCEPT
# service iptables save
export FLASK_ENV=development
export FLASK_APP=backend_apis.py
# python -m flask run
python backend_apis.py
