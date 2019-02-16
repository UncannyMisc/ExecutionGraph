// automatically generated by the FlatBuffers compiler, do not modify

import * as NS15865320443877550707 from "./LogicSocket_generated";
/**
 * @constructor
 */
export namespace executionGraph.serialization{
export class LogicNode {
  bb: flatbuffers.ByteBuffer|null = null;

  bb_pos:number = 0;
/**
 * @param number i
 * @param flatbuffers.ByteBuffer bb
 * @returns LogicNode
 */
__init(i:number, bb:flatbuffers.ByteBuffer):LogicNode {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param flatbuffers.ByteBuffer bb
 * @param LogicNode= obj
 * @returns LogicNode
 */
static getRoot(bb:flatbuffers.ByteBuffer, obj?:LogicNode):LogicNode {
  return (obj || new LogicNode).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @returns flatbuffers.Long
 */
id():flatbuffers.Long {
  var offset = this.bb!.__offset(this.bb_pos, 4);
  return offset ? this.bb!.readUint64(this.bb_pos + offset) : this.bb!.createLong(0, 0);
};

/**
 * @param flatbuffers.Encoding= optionalEncoding
 * @returns string|Uint8Array|null
 */
type():string|null
type(optionalEncoding:flatbuffers.Encoding):string|Uint8Array|null
type(optionalEncoding?:any):string|Uint8Array|null {
  var offset = this.bb!.__offset(this.bb_pos, 6);
  return offset ? this.bb!.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param number index
 * @param executionGraph.serialization.LogicSocket= obj
 * @returns executionGraph.serialization.LogicSocket
 */
inputSockets(index: number, obj?:NS15865320443877550707.executionGraph.serialization.LogicSocket):NS15865320443877550707.executionGraph.serialization.LogicSocket|null {
  var offset = this.bb!.__offset(this.bb_pos, 8);
  return offset ? (obj || new NS15865320443877550707.executionGraph.serialization.LogicSocket).__init(this.bb!.__indirect(this.bb!.__vector(this.bb_pos + offset) + index * 4), this.bb!) : null;
};

/**
 * @returns number
 */
inputSocketsLength():number {
  var offset = this.bb!.__offset(this.bb_pos, 8);
  return offset ? this.bb!.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @param number index
 * @param executionGraph.serialization.LogicSocket= obj
 * @returns executionGraph.serialization.LogicSocket
 */
outputSockets(index: number, obj?:NS15865320443877550707.executionGraph.serialization.LogicSocket):NS15865320443877550707.executionGraph.serialization.LogicSocket|null {
  var offset = this.bb!.__offset(this.bb_pos, 10);
  return offset ? (obj || new NS15865320443877550707.executionGraph.serialization.LogicSocket).__init(this.bb!.__indirect(this.bb!.__vector(this.bb_pos + offset) + index * 4), this.bb!) : null;
};

/**
 * @returns number
 */
outputSocketsLength():number {
  var offset = this.bb!.__offset(this.bb_pos, 10);
  return offset ? this.bb!.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @param number index
 * @returns number
 */
data(index: number):number|null {
  var offset = this.bb!.__offset(this.bb_pos, 12);
  return offset ? this.bb!.readUint8(this.bb!.__vector(this.bb_pos + offset) + index) : 0;
};

/**
 * @returns number
 */
dataLength():number {
  var offset = this.bb!.__offset(this.bb_pos, 12);
  return offset ? this.bb!.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @returns Uint8Array
 */
dataArray():Uint8Array|null {
  var offset = this.bb!.__offset(this.bb_pos, 12);
  return offset ? new Uint8Array(this.bb!.bytes().buffer, this.bb!.bytes().byteOffset + this.bb!.__vector(this.bb_pos + offset), this.bb!.__vector_len(this.bb_pos + offset)) : null;
};

/**
 * @param flatbuffers.Builder builder
 */
static start(builder:flatbuffers.Builder) {
  builder.startObject(5);
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Long id
 */
static addId(builder:flatbuffers.Builder, id:flatbuffers.Long) {
  builder.addFieldInt64(0, id, builder.createLong(0, 0));
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Offset typeOffset
 */
static addType(builder:flatbuffers.Builder, typeOffset:flatbuffers.Offset) {
  builder.addFieldOffset(1, typeOffset, 0);
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Offset inputSocketsOffset
 */
static addInputSockets(builder:flatbuffers.Builder, inputSocketsOffset:flatbuffers.Offset) {
  builder.addFieldOffset(2, inputSocketsOffset, 0);
};

/**
 * @param flatbuffers.Builder builder
 * @param Array.<flatbuffers.Offset> data
 * @returns flatbuffers.Offset
 */
static createInputSocketsVector(builder:flatbuffers.Builder, data:flatbuffers.Offset[]):flatbuffers.Offset {
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
static startInputSocketsVector(builder:flatbuffers.Builder, numElems:number) {
  builder.startVector(4, numElems, 4);
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Offset outputSocketsOffset
 */
static addOutputSockets(builder:flatbuffers.Builder, outputSocketsOffset:flatbuffers.Offset) {
  builder.addFieldOffset(3, outputSocketsOffset, 0);
};

/**
 * @param flatbuffers.Builder builder
 * @param Array.<flatbuffers.Offset> data
 * @returns flatbuffers.Offset
 */
static createOutputSocketsVector(builder:flatbuffers.Builder, data:flatbuffers.Offset[]):flatbuffers.Offset {
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
static startOutputSocketsVector(builder:flatbuffers.Builder, numElems:number) {
  builder.startVector(4, numElems, 4);
};

/**
 * @param flatbuffers.Builder builder
 * @param flatbuffers.Offset dataOffset
 */
static addData(builder:flatbuffers.Builder, dataOffset:flatbuffers.Offset) {
  builder.addFieldOffset(4, dataOffset, 0);
};

/**
 * @param flatbuffers.Builder builder
 * @param Array.<number> data
 * @returns flatbuffers.Offset
 */
static createDataVector(builder:flatbuffers.Builder, data:number[] | Uint8Array):flatbuffers.Offset {
  builder.startVector(1, data.length, 1);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addInt8(data[i]);
  }
  return builder.endVector();
};

/**
 * @param flatbuffers.Builder builder
 * @param number numElems
 */
static startDataVector(builder:flatbuffers.Builder, numElems:number) {
  builder.startVector(1, numElems, 1);
};

/**
 * @param flatbuffers.Builder builder
 * @returns flatbuffers.Offset
 */
static end(builder:flatbuffers.Builder):flatbuffers.Offset {
  var offset = builder.endObject();
  builder.requiredField(offset, 6); // type
  return offset;
};

static create(builder:flatbuffers.Builder, id:flatbuffers.Long, typeOffset:flatbuffers.Offset, inputSocketsOffset:flatbuffers.Offset, outputSocketsOffset:flatbuffers.Offset, dataOffset:flatbuffers.Offset):flatbuffers.Offset {
  LogicNode.start(builder);
  LogicNode.addId(builder, id);
  LogicNode.addType(builder, typeOffset);
  LogicNode.addInputSockets(builder, inputSocketsOffset);
  LogicNode.addOutputSockets(builder, outputSocketsOffset);
  LogicNode.addData(builder, dataOffset);
  return LogicNode.end(builder);
}
}
}
