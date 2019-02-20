//basic arguments
var args = {
	//web socket address on our local machine
ws_uri: "ws://" + location.hostname + ":8888/kurento",
	ice_servers: undefined
}

window.addEventListener('load', function(){

		//this is our stream from webcam
		var webRtcPeer;
		//constructor where we add different mediaobjects
		var pipeline;

		//video from webcam
		var videoInput = document.getElementById('videoInput');
		//video stream which is sent to media server and back to browser
		var videoOutput = document.getElementById('videoOutput');

		//start streaming
		var startButton = document.getElementById('start');
		//stop streaming
		var stopButton = document.getElementById('stop');

		//on start button click
		startButton.addEventListener('click', function(){

			var options = {
localVideo: videoInput,
remoteVideo: videoOutput
};

if(args.ice_servers){
options.configuration = {
iceServers:JSON.parse(args.ice_servers)
};
}

//local stream starts working
webRtcPeer = kurentoUtils.WebRtcPeer.WebRtcPeerSendrecv(options, function(error){
	if(error) return onError(error);
	//callback for receiving SDP offer
	//SDP is used for negotiating media exchanges between applications
	this.generateOffer(onOffer);
	});

//when application want to connect to our media server
function onOffer(error, sdpOffer){

	if(error) return onError(error);

	//kurentoClient is used for managing KMS API
	kurentoClient(args.ws_uri, function(error, client){

			if(error) return onError(error);

			//creating pipeline, constructor for media objects
			client.create("MediaPipeline", function(error, _pipeline){

				if(error) return onError(error);
				pipeline = _pipeline;

				//adding object WebRtcEndpoint
				//it is a media element with the capability of receiving and sending WebRTC flows
				pipeline.create("WebRtcEndpoint", function(error, webRtc){

					if(error) return onError(error);

					//setting callbacks when we are ready to connect our webcam peer with KMS
					setIceCandidateCallbacks(webRtcPeer, webRtc, onError);

					//finishing SDP
					webRtc.processOffer(sdpOffer, function(error, sdpAnswer){
						if(error) return onError(error);
						webRtcPeer.processAnswer(sdpAnswer, onError);
						});
					webRtc.gatherCandidates(onError);

					//connecting WebRTCEndpoint to itself
					webRtc.connect(webRtc, function(error){
						if(error) return onError(error);
						});

					});

			});
	});
}

});

function setIceCandidateCallbacks(webRtcPeer, webRtcEp, error){

	webRtcPeer.on('icecandidate', function(candidate){
			candidate = kurentoClient.register.complexTypes.IceCandidate(candidate);
			webRtcEp.addIceCandidate(candidate, onerror);
			});

	webRtcEp.on("OnIceCandidate", function(event){
			var candidate = event.candidate;
			webRtcPeer.addIceCandidate(candidate, onerror);
			});

}

stopButton.addEventListener("click", stop);

//remove our webcam peer and pipeline
function stop(){
	if(webRtcPeer){
		webRtcPeer.dispose();
		webRtcPeer = null;
	}
	if(pipeline){
		pipeline.release();
		pipeline = null;
	}
}

function onError(error){
	if(error){
		console.error(error);
		stop();
	}
}

});
