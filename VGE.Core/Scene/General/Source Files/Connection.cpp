// Source file for the Connection class
#include "Connection.h"

namespace VGE
{
	Connection::Connection(std::shared_ptr<Node> source, std::shared_ptr<Node> target, std::shared_ptr<Pin> sourcePin, std::shared_ptr<Pin> targetPin)
		: Source(source), Target(target), SourcePin(sourcePin), TargetPin(targetPin)
	{
	}
	Connection::~Connection()
	{
	}
	bool Connection::IsValid() const
	{
		return Source && Target && SourcePin && TargetPin && !IsCircularConnection();
	}
	bool Connection::IsCircularConnection() const
	{
		// Check if the source node is the same as the target node
		return Source == Target;
	}
} // namespace VGE

