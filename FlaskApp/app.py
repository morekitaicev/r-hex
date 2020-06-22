from flask import Flask, render_template, request
import subprocess
import os

app = Flask(__name__)


HOST="ssh pi@25.92.8.30"
COMMAND="rosrun photo_package talk_node.py"

@app.route('/button')
def start_roscore():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 roscore",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print(error)
    else:
        print(result)
    return render_template('index.html')


@app.route('/button')
def stop():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 rostopic pub stop std_msgs/String \"data: ''\" --once",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print(error)
    else:
        print(result)
    return render_template('index.html')

@app.route('/button')
def set_start():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 rostopic pub setStart std_msgs/String \"data: ''\" --once",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print(error)
    else:
        print(result)
    return render_template('index.html')

@app.route('/button')
def leg0():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 rostopic pub go0 std_msgs/String \"data: ''\" --once",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print(error)
    else:
        print(result)
    return render_template('index.html')

@app.route('/button')
def leg1():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 rostopic pub go1 std_msgs/String \"data: ''\" --once",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print(error)
    else:
        print(result)
    return render_template('index.html')

@app.route('/button')
def leg2():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 rostopic pub go2 std_msgs/String \"data: ''\" --once",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print(error)
    else:
        print(result)
    return render_template('index.html')

@app.route('/button')
def leg3():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 rostopic pub go3 std_msgs/String \"data: ''\" --once",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print(error)
    else:
        print(result)
    return render_template('index.html')

@app.route('/button')
def leg4():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 rostopic pub go4 std_msgs/String \"data: ''\" --once",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print(error)
    else:
        print(result)
    return render_template('index.html')

@app.route('/button')
def leg5():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 rostopic pub go5 std_msgs/String \"data: ''\" --once",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    result = ssh.stdout.readlines()
    if result == []:
        error = ssh.stderr.readlines()
        print(error)
    else:
        print(result)
    return render_template('index.html')

@app.route('/button')
def kill():
    ssh = subprocess.Popen("ssh pi@25.92.8.30 kill -9 roscore",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    ssh = subprocess.Popen("ssh pi@25.92.8.30 kill -9 rosmaster",
                           shell=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE)
    return render_template('index.html')

@app.route("/", methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        # name == value
        if request.form.get('roscore kek') == 'roscore':
            start_roscore()
        elif request.form.get('stop') == 'stop':
            stop()
        elif request.form.get('subject') == 'set start':
            set_start()
        elif request.form.get('subject') == 'Leg 1':
            leg0()
        elif request.form.get('subject') == 'Leg 2':
            leg1()
        elif request.form.get('subject') == 'Leg 3':
            leg2()
        elif request.form.get('subject') == 'Leg 4':
            leg3()
        elif request.form.get('subject') == 'Leg 5':
            leg4()
        elif request.form.get('subject') == 'Leg 6':
            leg5()
        elif request.form.get('kill roscore') == 'kill':
            kill()
        else:
            return render_template("index.html")
    elif request.method == 'GET':
        print("No Post Back Call")
    return render_template("index.html")

if __name__ == '__main__':
    app.run(debug=True)