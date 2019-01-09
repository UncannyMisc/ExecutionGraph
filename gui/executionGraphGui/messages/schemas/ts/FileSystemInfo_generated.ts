// automatically generated by the FlatBuffers compiler, do not modify

/**
 * @enum
 */
export namespace executionGraphGui.serialization{
export enum Permissions{
  None= 0,
  OwnerRead= 1,
  OwnerWrite= 2,
  OwnerReadWrite= 3
}};

/**
 * @constructor
 */
export namespace executionGraphGui.serialization{
export class PathInfo {
  bb: flatbuffers.ByteBuffer|null = null;

  bb_pos:number = 0;
/**
 * @param number i
 * @param flatbuffers.ByteBuffer bb
 * @returns PathInfo
 */
__init(i:number, bb:flatbuffers.ByteBuffer):PathInfo {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param flatbuffers.ByteBuffer bb
 * @param PathInfo= obj
 * @returns PathInfo
 */
static getRootAsPathInfo(bb:flatbuffers.ByteBuffer, obj?:PathInfo):PathInfo {
  return (obj || new PathInfo).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param flatbuffers.Encoding= optionalEncoding
 * @returns string|Uint8Array|null
 */
path():string|null
path(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
path(optionalEncoding?:any):string|Uint8Array|null {
  var offset = this.bb!.__offset(this.bb_pos, 4);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @returns executionGraphGui.serialization.Permissions
 */
permissions():executionGraphGui.serialization.Permissions {
  var offset = this.bb!.__offset(this.bb_pos, 6);
  return offset ? /**  */ (this.bb!.readInt8(this.bb_pos + offset)) : executionGraphGui.serialization.Permissions.None;
};

/**
 * @returns flatbuffers.Long
 */
size():flatbuffers.Long {
  var offset = this.bb!.__offset(this.bb_pos, 8);
  return offset ? this.bb!.readUint64(this.bb_pos + offset) : this.bb!.createLong(0, 0);
};

/**
 * @param flatbuffers.Encoding= optionalEncoding
 * @returns string|Uint8Array|null
 */
modified():string|null
modified(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
modified(optionalEncoding?:any):string|Uint8Array|null {
  var offset = this.bb!.__offset(this.bb_pos, 10);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param number index
 * @param executionGraphGui.serialization.PathInfo= obj
 * @returns executionGraphGui.serialization.PathInfo
 */
containedFiles(index: number, obj?:executionGraphGui.serialization.PathInfo):executionGraphGui.serialization.PathInfo|null {
  var offset = this.bb!.__offset(this.bb_pos, 12);
  return offset ? (obj || new executionGraphGui.serialization.PathInfo).__init(this.bb!.__indirect(this.bb!.__vector(this.bb_pos + offset) + index * 4), this.bb!) : null;
};

/**
 * @returns number
 */
containedFilesLength():number {
  var offset = this.bb!.__offset(this.bb_pos, 12);
  return offset ? this.bb!.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @param number index
 * @param executionGraphGui.serialization.PathInfo= obj
 * @returns executionGraphGui.serialization.PathInfo
 */
containedDirectories(index: number, obj?:executionGraphGui.serialization.PathInfo):executionGraphGui.serialization.PathInfo|null {
  var offset = this.bb!.__offset(this.bb_pos, 14);
  return offset ? (obj || new executionGraphGui.serialization.PathInfo).__init(this.bb!.__indirect(this.bb!.__vector(this.bb_pos + offset) + index * 4), this.bb!) : null;
};

/**
 * @returns number
 */
containedDirectoriesLength():number {
  var offset = this.bb!.__offset(this.bb_pos, 14);
  return offset ? this.bb!.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @param flatbuffers.Builder builder
 */
static startPathInfo(builder:flatbuffers.Builder) {
  builder.startObject(6);
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Offset pathOffset
 */
static addPath(builder:flatbuffers.Builder, pathOffset:flatbuffers.Offset) {
  builder.addFieldOffset(0, pathOffset, 0);
};

/**
 * @param flatbuffers.Builder builder
 * @param executionGraphGui.serialization.Permissions permissions
 */
static addPermissions(builder:flatbuffers.Builder, permissions:executionGraphGui.serialization.Permissions) {
  builder.addFieldInt8(1, permissions, executionGraphGui.serialization.Permissions.None);
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Long size
 */
static addSize(builder:flatbuffers.Builder, size:flatbuffers.Long) {
  builder.addFieldInt64(2, size, builder.createLong(0, 0));
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Offset modifiedOffset
 */
static addModified(builder:flatbuffers.Builder, modifiedOffset:flatbuffers.Offset) {
  builder.addFieldOffset(3, modifiedOffset, 0);
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Offset containedFilesOffset
 */
static addContainedFiles(builder:flatbuffers.Builder, containedFilesOffset:flatbuffers.Offset) {
  builder.addFieldOffset(4, containedFilesOffset, 0);
};

/**
 * @param flatbuffers.Builder builder
 * @param Array.<flatbuffers.Offset> data
 * @returns flatbuffers.Offset
 */
static createContainedFilesVector(builder:flatbuffers.Builder, data:flatbuffers.Offset[]):flatbuffers.Offset {
  builder.startVector(4, data.length, 4);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addOffset(data[i]);
  }
  return builder.endVector();
};

/**
 * @param flatbuffers.Builder builder
 * @param number numElems
 */
static startContainedFilesVector(builder:flatbuffers.Builder, numElems:number) {
  builder.startVector(4, numElems, 4);
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Offset containedDirectoriesOffset
 */
static addContainedDirectories(builder:flatbuffers.Builder, containedDirectoriesOffset:flatbuffers.Offset) {
  builder.addFieldOffset(5, containedDirectoriesOffset, 0);
};

/**
 * @param flatbuffers.Builder builder
 * @param Array.<flatbuffers.Offset> data
 * @returns flatbuffers.Offset
 */
static createContainedDirectoriesVector(builder:flatbuffers.Builder, data:flatbuffers.Offset[]):flatbuffers.Offset {
  builder.startVector(4, data.length, 4);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addOffset(data[i]);
  }
  return builder.endVector();
};

/**
 * @param flatbuffers.Builder builder
 * @param number numElems
 */
static startContainedDirectoriesVector(builder:flatbuffers.Builder, numElems:number) {
  builder.startVector(4, numElems, 4);
};

/**
 * @param flatbuffers.Builder builder
 * @returns flatbuffers.Offset
 */
static endPathInfo(builder:flatbuffers.Builder):flatbuffers.Offset {
  var offset = builder.endObject();
  builder.requiredField(offset, 4); // path
  builder.requiredField(offset, 10); // modified
  return offset;
};

static createPathInfo(builder:flatbuffers.Builder, pathOffset:flatbuffers.Offset, permissions:executionGraphGui.serialization.Permissions, size:flatbuffers.Long, modifiedOffset:flatbuffers.Offset, containedFilesOffset:flatbuffers.Offset, containedDirectoriesOffset:flatbuffers.Offset):flatbuffers.Offset {
  PathInfo.startPathInfo(builder);
  PathInfo.addPath(builder, pathOffset);
  PathInfo.addPermissions(builder, permissions);
  PathInfo.addSize(builder, size);
  PathInfo.addModified(builder, modifiedOffset);
  PathInfo.addContainedFiles(builder, containedFilesOffset);
  PathInfo.addContainedDirectories(builder, containedDirectoriesOffset);
  return PathInfo.endPathInfo(builder);
}
}
}
