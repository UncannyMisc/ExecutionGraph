// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_NODETYPEDESCRIPTION_EXECUTIONGRAPH_SERIALIZATION_H_
#define FLATBUFFERS_GENERATED_NODETYPEDESCRIPTION_EXECUTIONGRAPH_SERIALIZATION_H_

#include "flatbuffers/flatbuffers.h"

namespace executionGraph {
namespace serialization {

struct NodeTypeDescription;

struct NodeTypeDescription FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TYPE = 4,
    VT_NAME = 6,
    VT_INSOCKETNAMES = 8,
    VT_OUTSOCKETNAMES = 10,
    VT_DESCRIPTION = 12
  };
  const flatbuffers::String *type() const {
    return GetPointer<const flatbuffers::String *>(VT_TYPE);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *inSocketNames() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_INSOCKETNAMES);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *outSocketNames() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_OUTSOCKETNAMES);
  }
  const flatbuffers::String *description() const {
    return GetPointer<const flatbuffers::String *>(VT_DESCRIPTION);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffsetRequired(verifier, VT_TYPE) &&
           verifier.VerifyString(type()) &&
           VerifyOffsetRequired(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_INSOCKETNAMES) &&
           verifier.VerifyVector(inSocketNames()) &&
           verifier.VerifyVectorOfStrings(inSocketNames()) &&
           VerifyOffset(verifier, VT_OUTSOCKETNAMES) &&
           verifier.VerifyVector(outSocketNames()) &&
           verifier.VerifyVectorOfStrings(outSocketNames()) &&
           VerifyOffset(verifier, VT_DESCRIPTION) &&
           verifier.VerifyString(description()) &&
           verifier.EndTable();
  }
};

struct NodeTypeDescriptionBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_type(flatbuffers::Offset<flatbuffers::String> type) {
    fbb_.AddOffset(NodeTypeDescription::VT_TYPE, type);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(NodeTypeDescription::VT_NAME, name);
  }
  void add_inSocketNames(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> inSocketNames) {
    fbb_.AddOffset(NodeTypeDescription::VT_INSOCKETNAMES, inSocketNames);
  }
  void add_outSocketNames(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> outSocketNames) {
    fbb_.AddOffset(NodeTypeDescription::VT_OUTSOCKETNAMES, outSocketNames);
  }
  void add_description(flatbuffers::Offset<flatbuffers::String> description) {
    fbb_.AddOffset(NodeTypeDescription::VT_DESCRIPTION, description);
  }
  explicit NodeTypeDescriptionBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  NodeTypeDescriptionBuilder &operator=(const NodeTypeDescriptionBuilder &);
  flatbuffers::Offset<NodeTypeDescription> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<NodeTypeDescription>(end);
    fbb_.Required(o, NodeTypeDescription::VT_TYPE);
    fbb_.Required(o, NodeTypeDescription::VT_NAME);
    return o;
  }
};

inline flatbuffers::Offset<NodeTypeDescription> CreateNodeTypeDescription(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> type = 0,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> inSocketNames = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> outSocketNames = 0,
    flatbuffers::Offset<flatbuffers::String> description = 0) {
  NodeTypeDescriptionBuilder builder_(_fbb);
  builder_.add_description(description);
  builder_.add_outSocketNames(outSocketNames);
  builder_.add_inSocketNames(inSocketNames);
  builder_.add_name(name);
  builder_.add_type(type);
  return builder_.Finish();
}

inline flatbuffers::Offset<NodeTypeDescription> CreateNodeTypeDescriptionDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *type = nullptr,
    const char *name = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *inSocketNames = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *outSocketNames = nullptr,
    const char *description = nullptr) {
  auto type__ = type ? _fbb.CreateString(type) : 0;
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto inSocketNames__ = inSocketNames ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*inSocketNames) : 0;
  auto outSocketNames__ = outSocketNames ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*outSocketNames) : 0;
  auto description__ = description ? _fbb.CreateString(description) : 0;
  return executionGraph::serialization::CreateNodeTypeDescription(
      _fbb,
      type__,
      name__,
      inSocketNames__,
      outSocketNames__,
      description__);
}

}  // namespace serialization
}  // namespace executionGraph

#endif  // FLATBUFFERS_GENERATED_NODETYPEDESCRIPTION_EXECUTIONGRAPH_SERIALIZATION_H_
