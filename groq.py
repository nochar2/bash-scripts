#!/usr/bin/env python3
import requests
import os
import curses
import sys
import readline

# model = "llama3-8b-8192"
model = "llama3-70b-8192"

groq_api_key = os.environ.get("GROQ_API_KEY")
endpoint = "https://api.groq.com/openai/v1/chat/completions"
headers = {"Authorization": f"Bearer {groq_api_key}"}
data_template = {"messages": [{"role": "user", "content": "" } ], "model": model, max_tokens: 200}

while True:
	line = input("What do you want to help with? ")
	line = line.strip()
	if line == "":
		break
	data = data_template
	data["messages"][0]["content"] = line
	r = requests.post(endpoint, json=data, headers=headers)
	msg = json.loads(r.content)
	print(msg.choices[0].message.content)

# while read -r line; do

	# curl --no-progress-meter -X POST  \
	     # -H "Authorization: Bearer $GROQ_API_KEY" \
	     # -H "Content-Type: application/json" \
	     # -d "$json" | jq -r ".choices[0].message.content"
# done
