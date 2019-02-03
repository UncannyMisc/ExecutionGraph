// automatically generated by the FlatBuffers compiler, do not modify

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
 * @enum
 */
executionGraphGui.serialization.Permissions = {
  None: 0, 0: 'None',
  OwnerRead: 1, 1: 'OwnerRead',
  OwnerWrite: 2, 2: 'OwnerWrite',
  OwnerReadWrite: 3, 3: 'OwnerReadWrite'
};

/**
 * @constructor
 */
executionGraphGui.serialization.Date = function() {
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
 * @returns {executionGraphGui.serialization.Date}
 */
executionGraphGui.serialization.Date.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.Date.prototype.sec = function() {
  return this.bb.readUint8(this.bb_pos);
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.Date.prototype.min = function() {
  return this.bb.readUint8(this.bb_pos + 1);
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.Date.prototype.hour = function() {
  return this.bb.readUint8(this.bb_pos + 2);
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.Date.prototype.day = function() {
  return this.bb.readUint8(this.bb_pos + 3);
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.Date.prototype.month = function() {
  return this.bb.readUint8(this.bb_pos + 4);
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.Date.prototype.year = function() {
  return this.bb.readUint16(this.bb_pos + 6);
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.Date.prototype.wday = function() {
  return this.bb.readUint8(this.bb_pos + 8);
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.Date.prototype.yday = function() {
  return this.bb.readUint16(this.bb_pos + 10);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} sec
 * @param {number} min
 * @param {number} hour
 * @param {number} day
 * @param {number} month
 * @param {number} year
 * @param {number} wday
 * @param {number} yday
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.Date.create = function(builder, sec, min, hour, day, month, year, wday, yday) {
  builder.prep(2, 12);
  builder.writeInt16(yday);
  builder.pad(1);
  builder.writeInt8(wday);
  builder.writeInt16(year);
  builder.pad(1);
  builder.writeInt8(month);
  builder.writeInt8(day);
  builder.writeInt8(hour);
  builder.writeInt8(min);
  builder.writeInt8(sec);
  return builder.offset();
};

/**
 * @constructor
 */
executionGraphGui.serialization.PathInfo = function() {
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
 * @returns {executionGraphGui.serialization.PathInfo}
 */
executionGraphGui.serialization.PathInfo.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param {flatbuffers.ByteBuffer} bb
 * @param {executionGraphGui.serialization.PathInfo=} obj
 * @returns {executionGraphGui.serialization.PathInfo}
 */
executionGraphGui.serialization.PathInfo.getRootAsPathInfo = function(bb, obj) {
  return (obj || new executionGraphGui.serialization.PathInfo).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array|null}
 */
executionGraphGui.serialization.PathInfo.prototype.path = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 4);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array|null}
 */
executionGraphGui.serialization.PathInfo.prototype.name = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 6);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @returns {executionGraphGui.serialization.Permissions}
 */
executionGraphGui.serialization.PathInfo.prototype.permissions = function() {
  var offset = this.bb.__offset(this.bb_pos, 8);
  return offset ? /** @type {executionGraphGui.serialization.Permissions} */ (this.bb.readInt8(this.bb_pos + offset)) : executionGraphGui.serialization.Permissions.None;
};

/**
 * @returns {flatbuffers.Long}
 */
executionGraphGui.serialization.PathInfo.prototype.size = function() {
  var offset = this.bb.__offset(this.bb_pos, 10);
  return offset ? this.bb.readUint64(this.bb_pos + offset) : this.bb.createLong(0, 0);
};

/**
 * @param {executionGraphGui.serialization.Date=} obj
 * @returns {executionGraphGui.serialization.Date|null}
 */
executionGraphGui.serialization.PathInfo.prototype.modified = function(obj) {
  var offset = this.bb.__offset(this.bb_pos, 12);
  return offset ? (obj || new executionGraphGui.serialization.Date).__init(this.bb_pos + offset, this.bb) : null;
};

/**
 * @returns {boolean}
 */
executionGraphGui.serialization.PathInfo.prototype.isFile = function() {
  var offset = this.bb.__offset(this.bb_pos, 14);
  return offset ? !!this.bb.readInt8(this.bb_pos + offset) : false;
};

/**
 * @param {number} index
 * @param {executionGraphGui.serialization.PathInfo=} obj
 * @returns {executionGraphGui.serialization.PathInfo}
 */
executionGraphGui.serialization.PathInfo.prototype.files = function(index, obj) {
  var offset = this.bb.__offset(this.bb_pos, 16);
  return offset ? (obj || new executionGraphGui.serialization.PathInfo).__init(this.bb.__indirect(this.bb.__vector(this.bb_pos + offset) + index * 4), this.bb) : null;
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.PathInfo.prototype.filesLength = function() {
  var offset = this.bb.__offset(this.bb_pos, 16);
  return offset ? this.bb.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @param {number} index
 * @param {executionGraphGui.serialization.PathInfo=} obj
 * @returns {executionGraphGui.serialization.PathInfo}
 */
executionGraphGui.serialization.PathInfo.prototype.directories = function(index, obj) {
  var offset = this.bb.__offset(this.bb_pos, 18);
  return offset ? (obj || new executionGraphGui.serialization.PathInfo).__init(this.bb.__indirect(this.bb.__vector(this.bb_pos + offset) + index * 4), this.bb) : null;
};

/**
 * @returns {number}
 */
executionGraphGui.serialization.PathInfo.prototype.directoriesLength = function() {
  var offset = this.bb.__offset(this.bb_pos, 18);
  return offset ? this.bb.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @returns {boolean}
 */
executionGraphGui.serialization.PathInfo.prototype.isExplored = function() {
  var offset = this.bb.__offset(this.bb_pos, 20);
  return offset ? !!this.bb.readInt8(this.bb_pos + offset) : false;
};

/**
 * @param {flatbuffers.Builder} builder
 */
executionGraphGui.serialization.PathInfo.start = function(builder) {
  builder.startObject(9);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} pathOffset
 */
executionGraphGui.serialization.PathInfo.addPath = function(builder, pathOffset) {
  builder.addFieldOffset(0, pathOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} nameOffset
 */
executionGraphGui.serialization.PathInfo.addName = function(builder, nameOffset) {
  builder.addFieldOffset(1, nameOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {executionGraphGui.serialization.Permissions} permissions
 */
executionGraphGui.serialization.PathInfo.addPermissions = function(builder, permissions) {
  builder.addFieldInt8(2, permissions, executionGraphGui.serialization.Permissions.None);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Long} size
 */
executionGraphGui.serialization.PathInfo.addSize = function(builder, size) {
  builder.addFieldInt64(3, size, builder.createLong(0, 0));
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} modifiedOffset
 */
executionGraphGui.serialization.PathInfo.addModified = function(builder, modifiedOffset) {
  builder.addFieldStruct(4, modifiedOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {boolean} isFile
 */
executionGraphGui.serialization.PathInfo.addIsFile = function(builder, isFile) {
  builder.addFieldInt8(5, +isFile, +false);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} filesOffset
 */
executionGraphGui.serialization.PathInfo.addFiles = function(builder, filesOffset) {
  builder.addFieldOffset(6, filesOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {Array.<flatbuffers.Offset>} data
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.PathInfo.createFilesVector = function(builder, data) {
  builder.startVector(4, data.length, 4);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addOffset(data[i]);
  }
  return builder.endVector();
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} numElems
 */
executionGraphGui.serialization.PathInfo.startFilesVector = function(builder, numElems) {
  builder.startVector(4, numElems, 4);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} directoriesOffset
 */
executionGraphGui.serialization.PathInfo.addDirectories = function(builder, directoriesOffset) {
  builder.addFieldOffset(7, directoriesOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {Array.<flatbuffers.Offset>} data
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.PathInfo.createDirectoriesVector = function(builder, data) {
  builder.startVector(4, data.length, 4);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addOffset(data[i]);
  }
  return builder.endVector();
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} numElems
 */
executionGraphGui.serialization.PathInfo.startDirectoriesVector = function(builder, numElems) {
  builder.startVector(4, numElems, 4);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {boolean} isExplored
 */
executionGraphGui.serialization.PathInfo.addIsExplored = function(builder, isExplored) {
  builder.addFieldInt8(8, +isExplored, +false);
};

/**
 * @param {flatbuffers.Builder} builder
 * @returns {flatbuffers.Offset}
 */
executionGraphGui.serialization.PathInfo.end = function(builder) {
  var offset = builder.endObject();
  builder.requiredField(offset, 4); // path
  builder.requiredField(offset, 6); // name
  builder.requiredField(offset, 12); // modified
  return offset;
};

// Exports for Node.js and RequireJS
this.executionGraphGui = executionGraphGui;
