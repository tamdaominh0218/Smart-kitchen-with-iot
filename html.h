const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>Do an 3</title>
</head>
<style>
@import url(https://fonts.googleapis.com/css?family=Montserrat);
@import url(https://fonts.googleapis.com/css?family=Advent+Pro:400,200);
*{margin: 0;padding: 0;}

body{
  background:#FFF;
  font-family:Montserrat,Arial,sans-serif;

}
h2{
  font-size:14px;
}
.widget{
  box-shadow:0 40px 10px 5px rgba(0,0,0,0.4);
  margin:100px auto;
  height: 330px;
  position: relative;
  width: 500px;
}

.upper{
 
background:#00A8A9;
  border-radius:5px 5px 5px 5px;
  font-family:'Advent Pro';
  font-weight:200;
  height:500px;
  width:600px;
}

.date{
  font-size:40px;
}
.year{
  font-size:30px;
  color:#c1c1c1;
}
.place{
  color:#222;
  font-size:40px;
}
.lower{
   border-radius:0 0 0 0;
  background:#f5f5f5;
  height:250px;
  padding:50px;
margin-top: 100px; 

}

.infos{
  list-style:none;
}
.info{
  color:#fff;
 
  height:100%;
  padding-top:30px;
  text-align:left;
  width:20%;
 display: inline-block;

}
.info span{
  display: inline-block;
  font-size:40px;
  margin-top:60px;
  float:left;
}
.weather p {
  font-size:20px;padding:10px 0;
}
.anim{animation:fade .8s linear;}

@keyframes fade{
  0%{opacity:0;}
  100%{opacity:1;}
}

a{
 text-align: center;
 text-decoration: none;
 color: white;
 font-size: 15px;
 font-weight: 500;
}

        .tabcontent {
          display: none;
          border: 1px solid #2ec54f;
          border-top: none;
        }
.b{width: 100px;height: 50px;font-size: 15px;color: #FFF;background-color:#00A8A9;border-radius: 10px;font-family:'Advent Pro';}
.t{width: 100px;height: 50px;font-size: 15px;color: #FFF;background-color:#d67c28;border-radius: 10px;font-family:'Advent Pro';}
</style>
<body>
<center>
  <div style="text-align: center;"><a style="align:center; font-size: 50px;font-family:Montserrat,Arial,sans-serif;color: #000">HE THONG GIAM SAT KHONG KHI PHONG HOC</a></div>
  <img src="http://ete.dut.udn.vn/theme/images/logo.jpg">
  <div class="upper" > 
  
    <ul class="infos">
      <li class="info temperature ">
        <h2 class="title">TEMPERATURE</h2>
        <span class='update' id="temperature">21</span>
      </li>

      <li class="info gas">
        <h2 class="title">GAS</h2>
        <span class='update' id="gas">0%</span>
      </li>

      <li class="info humidity">
        <h2 class="title">HUMIDITY</h2>
        <span class='update' id="humidity">23%</span>
      </li>


      <li class="info Pressure">
        <h2 class="title">PRESSURE</h2>
        <span class='update' id="pressure">23</span>
      </li>
     
    </ul>
<br>
<br>
<div class="lower">
    
 
  <h3>LOAD CONTROL</h3>
            <p>
                <tr>
                    <td><a href="/LEDON"><button class="b">LEDON</button></a></td>
                    <td><a href="/LEDOFF"><button class="b">LEDOFF</button></a></td>
                </tr>
                <br>
                <tr>
                    <td><a href="/FANON"><button class="t">FANON</button></a></td>
                    <td><a href="/FANOFF"><button class="t">FANOFF</button></a></td>
                </tr>


            </p>
 
  </div>


        
    </div>
</div>
<script>
setInterval(drawClock, 2000);
    
function drawClock(){
    var now = new Date();
    var hour = now.getHours();
    var minute = now.getMinutes();
    var second = now.getSeconds();


    //Get Humidity Temperature and Rain Data
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
      var txt = this.responseText;
      var obj = JSON.parse(txt); //Ref: https://www.w3schools.com/js/js_json_parse.asp
        document.getElementById("gas").innerHTML = obj.gas + "bpm";
        document.getElementById("temperature").innerHTML = Math.round(obj.temperature) + "&deg;C";
        document.getElementById("humidity").innerHTML = Math.round(obj.humidity) + "%";
        document.getElementById("pressure").innerHTML = Math.round(obj.pressure) + "hPa";
      };  
    }
   xhttp.open("GET", "readADC", true); //Handle readADC server on ESP8266
   xhttp.send();
}
</script>

</center>
</body>
</html>
)=====";
