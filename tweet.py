from requests_oauthlib import OAuth1Session
import os
import json
import sys

# export 'CONSUMER_KEY'='<your_consumer_key>'
# export 'CONSUMER_SECRET'='<your_consumer_secret>'

consumer_key = "****"
consumer_secret = "********"

var1 = "📡 There are {} active players! 🔥 {} in LT base, {} in Annihilation, {} in RPG and {} in other servers.".format(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5])

payload = {"text": var1}
oauth = OAuth1Session(
    consumer_key,
    client_secret=consumer_secret,
    resource_owner_key="******",
    resource_owner_secret="*********",
)

response = oauth.post(
    "https://api.twitter.com/2/tweets",
    json=payload,
)

if response.status_code != 201:
    raise Exception(
        "Request returned an error: {} {}".format(response.status_code, response.text)
    )

print("Response code: {}".format(response.status_code))
json_response = response.json()
print(json.dumps(json_response, indent=4, sort_keys=True))
