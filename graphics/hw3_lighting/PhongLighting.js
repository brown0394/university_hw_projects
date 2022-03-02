var gl;
//201824641 최성찬
function main()
{
	canvas = document.getElementById("mycanvas");
	gl = canvas.getContext("webgl");

	const pixelRatio = window.devicePixelRatio || 1;
	canvas.width  = pixelRatio * canvas.clientWidth;
	canvas.height = pixelRatio * canvas.clientHeight;
	gl.viewport(0, 0, canvas.width, canvas.height);
	gl.clearColor(1.0,1.0,1.0,0.0);
	gl.enable(gl.DEPTH_TEST);
	gl.enable(gl.CULL_FACE);
	gl.frontFace(gl.CCW);
	gl.cullFace(gl.BACK);


	// Create Shaders
	const vs_source = document.getElementById('vertexShader').text;
	const vs = gl.createShader(gl.VERTEX_SHADER);
	gl.shaderSource(vs, vs_source);
	gl.compileShader(vs);
	if ( ! gl.getShaderParameter(vs, gl.COMPILE_STATUS) ) {
		alert( gl.getShaderInfoLog(vs) );
		gl.deleteShader(vs);
	}


	const fs_source = document.getElementById('fragmentShader').text;
	const fs = gl.createShader(gl.FRAGMENT_SHADER);
	gl.shaderSource(fs, fs_source);
	gl.compileShader(fs);
	if ( ! gl.getShaderParameter(fs, gl.COMPILE_STATUS) ) {
		alert( gl.getShaderInfoLog(fs) );
		gl.deleteShader(fs);
	}

	prog = gl.createProgram();
	gl.attachShader(prog, vs);
	gl.attachShader(prog, fs);
	gl.linkProgram(prog);
	if ( ! gl.getProgramParameter(prog, gl.LINK_STATUS) ) {
		alert( gl.getProgramInfoLog(prog) );
	}


  positions = [];
  normals = [];
  indices = [];
  var sphere = createSphere();
  positions = new Float32Array(sphere.positions);
  normals = positions;
  indices = new Uint16Array(sphere.indices);


	var position_buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, position_buffer);
	gl.bufferData(gl.ARRAY_BUFFER, positions, gl.STATIC_DRAW);

	var normal_buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, normal_buffer);
	gl.bufferData(gl.ARRAY_BUFFER, normals, gl.STATIC_DRAW);

	var index_buffer = gl.createBuffer();
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, index_buffer);
	gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);

	var posAttribLoc = gl.getAttribLocation(prog, 'pos');
	gl.bindBuffer(gl.ARRAY_BUFFER, position_buffer);
	gl.vertexAttribPointer(posAttribLoc, 3, gl.FLOAT, false, 0, 0);
	gl.enableVertexAttribArray(posAttribLoc);
	
	var normalAttribLoc = gl.getAttribLocation(prog,'normal');
	gl.bindBuffer(gl.ARRAY_BUFFER, normal_buffer);
	gl.vertexAttribPointer(normalAttribLoc, 3, gl.FLOAT, false, 0, 0);
	gl.enableVertexAttribArray(normalAttribLoc);

	var worldMatrix = new Matrix4();
	var viewMatrix = new Matrix4();
	var projMatrix = new Matrix4();
	var nMatrix = new Matrix4();
	var eyePos = new Vector3([0.0, 5.0, -8.0]);
	var lightDirection = new Vector3([5.0,5.0,-8.0]);

	worldMatrix.setIdentity();
	viewMatrix.setLookAt(eyePos.elements[0],eyePos.elements[1],eyePos.elements[2],0,0,0,0,1,0);
	projMatrix.setPerspective(30,1,0.1,100);
	nMatrix.setInverseOf(worldMatrix);
	nMatrix.transpose();


	
	
	gl.useProgram(prog);
	var wM = gl.getUniformLocation(prog,'worldMat');
	var vM = gl.getUniformLocation(prog,'viewMat');
	var pM = gl.getUniformLocation(prog,'projMat');
	var nM = gl.getUniformLocation(prog,'normalMat');
	var uEye = gl.getUniformLocation(prog, 'eyePos');
	var uLightDir = gl.getUniformLocation(prog, 'lightDir');

	gl.uniformMatrix4fv( wM, false, worldMatrix.elements );
	gl.uniformMatrix4fv( vM, false, viewMatrix.elements );
	gl.uniformMatrix4fv( pM, false, projMatrix.elements );
	gl.uniformMatrix4fv( nM, false, nMatrix.elements );
	gl.uniform3fv(uEye, eyePos.elements);

	// HW3: set uniform variables for shaders for Phong lighting
	// TODO here
	var Matrix3 = function(opt_src) {
		var i, j, s, d;
		if (opt_src && typeof opt_src === 'object' && opt_src.hasOwnProperty('elements')) {
		  s = opt_src.elements;
		  d = new Float32Array(9);
		  j = 0;
		  for (i = 0; i < 9; ++i) {
			d[i] = s[j];
			++j;
			if (j == 3 || j == 7) {
				++j;
			}
		  }
		  this.elements = d;
		} else {
		  this.elements = new Float32Array([1,0,0, 0,1,0, 0,0,1]);
		}
	};
	Matrix3.prototype.transpose = function() {
		var e, t;
	  
		e = this.elements;
	  
		t = e[ 1];  e[ 1] = e[ 3];  e[ 3] = t;
		t = e[ 2];  e[ 2] = e[ 6];  e[ 6] = t;
		t = e[ 5];  e[ 5] = e[ 7];  e[ 7] = t;	  
		return this;
	};

	Matrix3.prototype.setInverseOf = function(other) {
		var i, s, d, inv, det, t;
	  
		s = other.elements;
		d = this.elements;
		inv = new Float32Array(9);
	  
		inv[0]  =   s[4]*s[8] - s[5]*s[7];
		inv[1]  = - s[3]*s[8] + s[5]*s[6];
		inv[2]  =   s[3]*s[7] - s[4]*s[6];
		inv[3]  = - s[1]*s[8] + s[2]*s[7];
		inv[4]  =   s[0]*s[8] - s[2]*s[6];
		inv[5]  = - s[0]*s[7] + s[1]*s[6];
		inv[6]  =   s[1]*s[5] - s[4]*s[2];
		inv[7]  = - s[0]*s[5] + s[2]*s[3];
		inv[8]  =   s[0]*s[4] - s[1]*s[3];
			  
		det = (s[6] * inv[6]) - (s[7] * inv[7]) + (s[8] * inv[8]);
		if (det === 0) {
		  return this;
		}

		t = inv[ 1];  inv[ 1] = inv[ 3];  inv[ 3] = t;
		t = inv[ 2];  inv[ 2] = inv[ 6];  inv[ 6] = t;
		t = inv[ 5];  inv[ 5] = inv[ 7];  inv[ 7] = t;

		det = 1 / det;
		for (i = 0; i < 9; i++) {
		  d[i] = inv[i] * det;
		}
	  
		return this;
	};
	var tiworldMatrix = new Matrix3(worldMatrix);
	tiworldMatrix.setInverseOf(tiworldMatrix);
	tiworldMatrix.transpose();
	console.log(tiworldMatrix.elements);
	var tiM = gl.getUniformLocation(prog,'tiMat');
	gl.uniformMatrix3fv( tiM, false, tiworldMatrix.elements );

	var matSpec = new Vector3([0.7, 0.7, 0.7]);
	var matAmbi = new Vector3([0.2, 0.2, 0.2]);
	var matEmit = new Vector3([0.2, 0.2, 0.0]);

	var srcDiff = new Vector3([1.0, 1.0, 1.0]);
	var srcSpec = new Vector3([1.0, 1.0, 1.0]);
	var srcAmbi = new Vector3([0.8, 0.8, 0.8]);

	var matSh = 32.0;
	var matDiff = new Vector3([1.0, 0.0, 0.0]);

	var mS = gl.getUniformLocation(prog,'matSpec');
	var mA = gl.getUniformLocation(prog,'matAmbi');
	var mE = gl.getUniformLocation(prog,'matEmit');

	var sD = gl.getUniformLocation(prog,'srcDiff');
	var sS = gl.getUniformLocation(prog, 'srcSpec');
	var sA = gl.getUniformLocation(prog, 'srcAmbi');

	var mSh = gl.getUniformLocation(prog, 'matSh');
	var mD = gl.getUniformLocation(prog, 'matDiff');

	gl.uniform3fv(uLightDir, lightDirection.elements);

	gl.uniform3fv(mS, matSpec.elements);
	gl.uniform3fv(mA, matAmbi.elements);
	gl.uniform3fv(mE, matEmit.elements);

	gl.uniform3fv(sD, srcDiff.elements);
	gl.uniform3fv(sS, srcSpec.elements);
	gl.uniform3fv(sA, srcAmbi.elements);

	gl.uniform3fv(mD, matDiff.elements);
	gl.uniform1f(mSh, matSh);
	




	var currentAngle = 0.0;
	var loop = function (){
		currentAngle = animate(currentAngle);
		var rotateM = new Matrix4();
		rotateM.setRotate(currentAngle, 0,1,0);
		rotatedLight = rotateM.multiplyVector3(lightDirection);
		gl.uniform3fv(uLightDir, rotatedLight.elements);
		gl.clear(gl.DEPTH_BUFFER_BIT | gl.COLOR_BUFFER_BIT);
		gl.drawElements(gl.TRIANGLES, indices.length, gl.UNSIGNED_SHORT, 0);
		requestAnimationFrame(loop);
	};
	requestAnimationFrame(loop);
}


function setSpeed(){
	var speed = document.getElementById('scaleBar').value;
	ANGLE_STEP = 30.0 * speed;
}

var ANGLE_STEP = 30.0;
var g_last = Date.now();
function animate(angle){
	var now = Date.now();
	var elapsed = now - g_last;
	g_last = now;
	var newAngle = angle + (ANGLE_STEP * elapsed) /1000.0;
	return newAngle %= 360;
}

function createSphere() { // Create a sphere
  var SPHERE_DIV = 23;

  var i, ai, si, ci;
  var j, aj, sj, cj;
  var p1, p2;

  var positions = [];
  var indices = [];

  // Generate coordinates
  for (j = 0; j <= SPHERE_DIV; j++) {
    aj = j * Math.PI / SPHERE_DIV;
    sj = Math.sin(aj);
    cj = Math.cos(aj);
    for (i = 0; i <= SPHERE_DIV; i++) {
      ai = i * 2 * Math.PI / SPHERE_DIV;
      si = Math.sin(ai);
      ci = Math.cos(ai);

      positions.push(si * sj);  // X
      positions.push(cj);       // Y
      positions.push(ci * sj);  // Z
    }
  }

  // Generate indices
  for (j = 0; j < SPHERE_DIV; j++) {
    for (i = 0; i < SPHERE_DIV; i++) {
      p1 = j * (SPHERE_DIV+1) + i;
      p2 = p1 + (SPHERE_DIV+1);

      indices.push(p1);
      indices.push(p2);
      indices.push(p1 + 1);

      indices.push(p1 + 1);
      indices.push(p2);
      indices.push(p2 + 1);
    }
  }
  return {
  	positions: positions,
  	indices: indices
  };
}