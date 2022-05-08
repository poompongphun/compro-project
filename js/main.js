const msgDiv = document.getElementById("message");
const statusDiv = document.getElementById("status");
const clinetid = `clientId-${Date.now()}`;
client = new Paho.MQTT.Client(
  "broker.mqttdashboard.com",
  Number(8000),
  clinetid
);
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

client.connect({ onSuccess: onConnect });

function onConnect() {
  console.log("onConnect");
  client.subscribe("swood");
  getIPs().then((res) => {
    message = new Paho.MQTT.Message(
      `${clinetid} Hello, I'm ${res.join('\n')}`
    );
    message.destinationName = "swood";
    client.send(message);
    statusDiv.innerHTML = `<i class="bi bi-wifi m-2" style="color:hsl(129, 59%, 49%)"></i><span class="signal" style="color:hsl(129, 59%, 49%)">Connected</span>`;
  });
}

function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost: " + responseObject.errorMessage);
    statusDiv.innerHTML = `<i class="bi bi-wifi-off m-2" style="color:hsl(1, 97%, 66%)"></i><span class="signal" style="color:hsl(1, 97%, 66%)">No signal</span>`;
  }
}

function onMessageArrived(message) {
  console.log("onMessageArrived: " + message.payloadString);
  let [name, ...text] = message.payloadString.split(" ");
  text = text.join(" ");
  msgDiv.innerHTML =
    `<div class="msg"><span class="name">${name}</span> <span class="text">${text}</span></div>` +
    msgDiv.innerHTML;
}
