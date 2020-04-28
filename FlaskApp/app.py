from flask import Flask, render_template, request
import time

app = Flask(__name__)

@app.route("/", methods=['GET', 'POST'])
def index():
    print(request.form.get('V1button.value'))
    #Test.v1 = request.form.get('V1button.value')
    if request.method == 'POST':
        if request.form.get('Stop') == 'Stop':
            print("Encrypted")
        else:
            return render_template("index.html")
    elif request.method == 'GET':
        print("No Post Back Call")
    return render_template("index.html")

if __name__ == "__main__":
    app.run()