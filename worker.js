self.onmessage = async function(e) 
{
  var file = e.data;
  var reader = new FileReader();
  reader.onload = async function(e) 
  {
    var stringdata = e.target.result;
    var data = new Uint8Array(new TextEncoder().encode(stringdata));
    var memory = _malloc(data.length);
    HEAPU8.set(data, memory);

    console.log("return = " + _LoadDXF(memory, data.length));
    _free(memory);

    var address = _GETdrawing();
    var drawinglength = _GETdrawinglength();
    var drawing = new Array(drawinglength);

    for (var i = 0; i < drawinglength; i++) {
      drawing[i] = new Line;
      drawing[i].p0 = new Point;
      drawing[i].p1 = new Point;
      drawing[i].p0.x = HEAPF64[address / 8 + 0];
      drawing[i].p0.y = HEAPF64[address / 8 + 1];
      drawing[i].p1.x = HEAPF64[address / 8 + 2];
      drawing[i].p1.y = HEAPF64[address / 8 + 3];
      address += 32;
    }

    self.postMessage(drawing);
  };
  reader.readAsText(file);
};