// automatically generated by the FlatBuffers compiler, do not modify

/**
 * @const
 * @namespace
 */
var executionGraph = executionGraph || {};

/**
 * @const
 * @namespace
 */
executionGraph.serialization = executionGraph.serialization || {};

/**
 * @const
 * @namespace
 */
var executionGraphGui = executionGraphGui || {};

/**
 * @const
 * @namespace
 */
executionGraphGui.serialization = executionGraphGui.serialization || {};

/**
 * @constructor
 */
executionGraphGui.serialization.AddGraphRequest = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {executionGraphGui.serialization.AddGraphRequest}
 */
executionGraphGui.serialization.AddGraphRequest.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param {flatbuffers.ByteBuffer} bb
 * @param {executionGraphGui.serialization.AddGraphRequest=} obj
 * @returns {executionGraphGui.serialization.AddGraphRequest}
 */
executionGraphGui.serialization.AddGraphRequest.getRootAsAddGraphRequest = function(bb, obj) {
  return (obj || new executionGraphGui.serialization.AddGraphRequest).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array|null}
 */
executionGraphGui.serialization.AddGraphRequest.prototype.graphTypeId = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 4);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param {flatbuffers.Builder} builder
 */
executionGraphGui.serialization.AddGraphRequest.start = function(builder) {
  builder.startObject(1);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} graphTypeIdOffset
 */
executionGraphGui.serialization.AddGraphRequest.addGraphTypeId = function(builder, graphTypeIdOffset) {
  builder.addFieldOffset(0, graphTypeIdOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.AddGraphRequest.end = function(builder) {
  var offset = builder.endObject();
  builder.requiredField(offset, 4); // graphTypeId
  return offset;
};

/**
 * @constructor
 */
executionGraphGui.serialization.AddGraphResponse = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {executionGraphGui.serialization.AddGraphResponse}
 */
executionGraphGui.serialization.AddGraphResponse.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param {flatbuffers.ByteBuffer} bb
 * @param {executionGraphGui.serialization.AddGraphResponse=} obj
 * @returns {executionGraphGui.serialization.AddGraphResponse}
 */
executionGraphGui.serialization.AddGraphResponse.getRootAsAddGraphResponse = function(bb, obj) {
  return (obj || new executionGraphGui.serialization.AddGraphResponse).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array|null}
 */
executionGraphGui.serialization.AddGraphResponse.prototype.graphId = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 4);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param {flatbuffers.Builder} builder
 */
executionGraphGui.serialization.AddGraphResponse.start = function(builder) {
  builder.startObject(1);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} graphIdOffset
 */
executionGraphGui.serialization.AddGraphResponse.addGraphId = function(builder, graphIdOffset) {
  builder.addFieldOffset(0, graphIdOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.AddGraphResponse.end = function(builder) {
  var offset = builder.endObject();
  builder.requiredField(offset, 4); // graphId
  return offset;
};

/**
 * @constructor
 */
executionGraphGui.serialization.RemoveGraphRequest = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {executionGraphGui.serialization.RemoveGraphRequest}
 */
executionGraphGui.serialization.RemoveGraphRequest.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param {flatbuffers.ByteBuffer} bb
 * @param {executionGraphGui.serialization.RemoveGraphRequest=} obj
 * @returns {executionGraphGui.serialization.RemoveGraphRequest}
 */
executionGraphGui.serialization.RemoveGraphRequest.getRootAsRemoveGraphRequest = function(bb, obj) {
  return (obj || new executionGraphGui.serialization.RemoveGraphRequest).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array|null}
 */
executionGraphGui.serialization.RemoveGraphRequest.prototype.graphId = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 4);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param {flatbuffers.Builder} builder
 */
executionGraphGui.serialization.RemoveGraphRequest.start = function(builder) {
  builder.startObject(1);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} graphIdOffset
 */
executionGraphGui.serialization.RemoveGraphRequest.addGraphId = function(builder, graphIdOffset) {
  builder.addFieldOffset(0, graphIdOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.RemoveGraphRequest.end = function(builder) {
  var offset = builder.endObject();
  builder.requiredField(offset, 4); // graphId
  return offset;
};

/**
 * @constructor
 */
executionGraphGui.serialization.LoadGraphRequest = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {executionGraphGui.serialization.LoadGraphRequest}
 */
executionGraphGui.serialization.LoadGraphRequest.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param {flatbuffers.ByteBuffer} bb
 * @param {executionGraphGui.serialization.LoadGraphRequest=} obj
 * @returns {executionGraphGui.serialization.LoadGraphRequest}
 */
executionGraphGui.serialization.LoadGraphRequest.getRootAsLoadGraphRequest = function(bb, obj) {
  return (obj || new executionGraphGui.serialization.LoadGraphRequest).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array|null}
 */
executionGraphGui.serialization.LoadGraphRequest.prototype.filePath = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 4);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param {flatbuffers.Builder} builder
 */
executionGraphGui.serialization.LoadGraphRequest.start = function(builder) {
  builder.startObject(1);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} filePathOffset
 */
executionGraphGui.serialization.LoadGraphRequest.addFilePath = function(builder, filePathOffset) {
  builder.addFieldOffset(0, filePathOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.LoadGraphRequest.end = function(builder) {
  var offset = builder.endObject();
  builder.requiredField(offset, 4); // filePath
  return offset;
};

/**
 * @constructor
 */
executionGraphGui.serialization.LoadGraphResponse = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {executionGraphGui.serialization.LoadGraphResponse}
 */
executionGraphGui.serialization.LoadGraphResponse.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param {flatbuffers.ByteBuffer} bb
 * @param {executionGraphGui.serialization.LoadGraphResponse=} obj
 * @returns {executionGraphGui.serialization.LoadGraphResponse}
 */
executionGraphGui.serialization.LoadGraphResponse.getRootAsLoadGraphResponse = function(bb, obj) {
  return (obj || new executionGraphGui.serialization.LoadGraphResponse).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param {executionGraph.serialization.ExecutionGraph=} obj
 * @returns {executionGraph.serialization.ExecutionGraph|null}
 */
executionGraphGui.serialization.LoadGraphResponse.prototype.graph = function(obj) {
  var offset = this.bb.__offset(this.bb_pos, 4);
  return offset ? (obj || new executionGraph.serialization.ExecutionGraph).__init(this.bb.__indirect(this.bb_pos + offset), this.bb) : null;
};

/**
 * @param {flatbuffers.Builder} builder
 */
executionGraphGui.serialization.LoadGraphResponse.start = function(builder) {
  builder.startObject(1);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} graphOffset
 */
executionGraphGui.serialization.LoadGraphResponse.addGraph = function(builder, graphOffset) {
  builder.addFieldOffset(0, graphOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.LoadGraphResponse.end = function(builder) {
  var offset = builder.endObject();
  builder.requiredField(offset, 4); // graph
  return offset;
};

/**
 * @constructor
 */
executionGraphGui.serialization.SaveGraphRequest = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {executionGraphGui.serialization.SaveGraphRequest}
 */
executionGraphGui.serialization.SaveGraphRequest.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param {flatbuffers.ByteBuffer} bb
 * @param {executionGraphGui.serialization.SaveGraphRequest=} obj
 * @returns {executionGraphGui.serialization.SaveGraphRequest}
 */
executionGraphGui.serialization.SaveGraphRequest.getRootAsSaveGraphRequest = function(bb, obj) {
  return (obj || new executionGraphGui.serialization.SaveGraphRequest).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array|null}
 */
executionGraphGui.serialization.SaveGraphRequest.prototype.graphId = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 4);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array|null}
 */
executionGraphGui.serialization.SaveGraphRequest.prototype.filePath = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 6);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @returns {boolean}
 */
executionGraphGui.serialization.SaveGraphRequest.prototype.overwrite = function() {
  var offset = this.bb.__offset(this.bb_pos, 8);
  return offset ? !!this.bb.readInt8(this.bb_pos + offset) : false;
};

/**
 * @param {number} index
 * @returns {number}
 */
executionGraphGui.serialization.SaveGraphRequest.prototype.visualization = function(index) {
  var offset = this.bb.__offset(this.bb_pos, 10);
  return offset ? this.bb.readUint8(this.bb.__vector(this.bb_pos + offset) + index) : 0;
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.SaveGraphRequest.prototype.visualizationLength = function() {
  var offset = this.bb.__offset(this.bb_pos, 10);
  return offset ? this.bb.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @returns {Uint8Array}
 */
executionGraphGui.serialization.SaveGraphRequest.prototype.visualizationArray = function() {
  var offset = this.bb.__offset(this.bb_pos, 10);
  return offset ? new Uint8Array(this.bb.bytes().buffer, this.bb.bytes().byteOffset + this.bb.__vector(this.bb_pos + offset), this.bb.__vector_len(this.bb_pos + offset)) : null;
};

/**
 * @param {flatbuffers.Builder} builder
 */
executionGraphGui.serialization.SaveGraphRequest.start = function(builder) {
  builder.startObject(4);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} graphIdOffset
 */
executionGraphGui.serialization.SaveGraphRequest.addGraphId = function(builder, graphIdOffset) {
  builder.addFieldOffset(0, graphIdOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} filePathOffset
 */
executionGraphGui.serialization.SaveGraphRequest.addFilePath = function(builder, filePathOffset) {
  builder.addFieldOffset(1, filePathOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {boolean} overwrite
 */
executionGraphGui.serialization.SaveGraphRequest.addOverwrite = function(builder, overwrite) {
  builder.addFieldInt8(2, +overwrite, +false);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} visualizationOffset
 */
executionGraphGui.serialization.SaveGraphRequest.addVisualization = function(builder, visualizationOffset) {
  builder.addFieldOffset(3, visualizationOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {Array.<number>} data
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.SaveGraphRequest.createVisualizationVector = function(builder, data) {
  builder.startVector(1, data.length, 1);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addInt8(data[i]);
  }
  return builder.endVector();
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} numElems
 */
executionGraphGui.serialization.SaveGraphRequest.startVisualizationVector = function(builder, numElems) {
  builder.startVector(1, numElems, 1);
};

/**
 * @param {flatbuffers.Builder} builder
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.SaveGraphRequest.end = function(builder) {
  var offset = builder.endObject();
  builder.requiredField(offset, 4); // graphId
  builder.requiredField(offset, 6); // filePath
  return offset;
};

// Exports for Node.js and RequireJS
this.executionGraph = executionGraph;
this.executionGraphGui = executionGraphGui;
