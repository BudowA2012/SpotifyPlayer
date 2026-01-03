from flask import Flask, jsonify
import spotipy
from spotipy.oauth2 import SpotifyOAuth

# Wprowadź swoje dane klienta Spotify
CLIENT_ID = "8da03aba77874b5fa7993cf9236431f8"
CLIENT_SECRET = "ddc1d3b5ae984e57927dc22b237ac9be"
REDIRECT_URI = "http://127.0.0.1:8888/callback"
SCOPE = "user-read-currently-playing"

sp_oauth = SpotifyOAuth(client_id=CLIENT_ID,
                        client_secret=CLIENT_SECRET,
                        redirect_uri=REDIRECT_URI,
                        scope=SCOPE)

token_info = sp_oauth.get_access_token(as_dict=False)
sp = spotipy.Spotify(auth=token_info)

app = Flask(__name__)

@app.route("/now")
def now_playing():
    current = sp.currently_playing()
    if current and current.get("item"):
        track = current["item"]["name"]
        artist = current["item"]["artists"][0]["name"]
        progress_ms = current["progress_ms"]
        duration_ms = current["item"]["duration_ms"]
        return jsonify({
            "track": track,
            "artist": artist,
            "progress_ms": progress_ms,
            "duration_ms": duration_ms
        })
    else:
        return jsonify({
            "track": "—",
            "artist": "—",
            "progress_ms": 0,
            "duration_ms": 1
        })

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
