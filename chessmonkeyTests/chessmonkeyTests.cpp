#include "pch.h"
#include "CppUnitTest.h"
#include "../chessmonkey/src/Game.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<> static std::wstring ToString<Square>(const Square& square)
			{
				const wchar_t s[3] = { square.file, square.rank, '\0' };
				return s;
			};
			template<> static std::wstring ToString<TypeofPiece>(const TypeofPiece& type)
			{
				switch (type) {
				case TypeofPiece::_:
					return L" ";
				case TypeofPiece::p:
					return L"P";
				case TypeofPiece::K:
					return L"K";
				case TypeofPiece::Q:
					return L"Q";
				case TypeofPiece::B:
					return L"B";
				case TypeofPiece::N:
					return L"N";
				case TypeofPiece::R:
					return L"R";
				default:
					return L" ";
				}
			};
			template<> static std::wstring ToString<Castle>(const Castle& c)
			{
				switch (c) {
				case Castle::_:
					return L" ";
				case Castle::Short:
					return L"Short Castle";
				case Castle::Long:
					return L"Long Castle";
				default:
					return L" ";
				}
			};
			template<> static std::wstring ToString<PieceColor>(const PieceColor& pc)
			{
				switch (pc) {
				case PieceColor::_:
					return L" ";
				case PieceColor::Black:
					return L"Black";
				case PieceColor::White:
					return L"White";
				default:
					return L" ";
				}
			};
		}
	}
}

namespace chessmonkeyTests
{
	TEST_CLASS(Game_Tests) {

	public:
		/*
		Square destination;
		Piece piece;
		bool captures = 0;
		bool check = 0;
		bool checkmate = 0;
		TypeofPiece promotion = TypeofPiece::_;
		Castle castles = Castle::_;
		*/
		TEST_METHOD(test_moveStringParse) {
			// Test pawn move
			std::string testString = "a4";
			Move result = moveStringParse(testString, PieceColor::Black);

			Assert::AreEqual(Square{ 'a', '4' }, result.destination);
			Assert::AreEqual(TypeofPiece::p, result.piece.type);
			Assert::AreEqual(PieceColor::Black, result.piece.color);
			Assert::AreEqual(Square{ 0, 0 }, result.piece.square);;
			Assert::AreEqual(false, result.captures);
			Assert::AreEqual(false, result.check);
			Assert::AreEqual(false, result.checkmate);
			Assert::AreEqual(TypeofPiece::_, result.promotion);
			Assert::AreEqual(Castle::_, result.castles);

			// Test Knight check move
			testString = "Ne7+";
			result = moveStringParse(testString, PieceColor::White);
			
			Assert::AreEqual(Square{ 'e', '7' }, result.destination);
			Assert::AreEqual(TypeofPiece::N, result.piece.type);
			Assert::AreEqual(PieceColor::White, result.piece.color);
			Assert::AreEqual(Square{ 0, 0 }, result.piece.square);;
			Assert::AreEqual(false, result.captures);
			Assert::AreEqual(true, result.check);
			Assert::AreEqual(false, result.checkmate);
			Assert::AreEqual(TypeofPiece::_, result.promotion);
			Assert::AreEqual(Castle::_, result.castles);
			

			// Test Disambiguation
			testString = "Rbd1";
			result = moveStringParse(testString, PieceColor::Black);

			Assert::AreEqual(Square{ 'd', '1' }, result.destination);
			Assert::AreEqual(TypeofPiece::R, result.piece.type);
			Assert::AreEqual(PieceColor::Black, result.piece.color);
			Assert::AreEqual(Square{ 'b', 0 }, result.piece.square);;
			Assert::AreEqual(false, result.captures);
			Assert::AreEqual(false, result.check);
			Assert::AreEqual(false, result.checkmate);
			Assert::AreEqual(TypeofPiece::_, result.promotion);
			Assert::AreEqual(Castle::_, result.castles);

			// Test Captures with pawn
			testString = "exf5";
			result = moveStringParse(testString, PieceColor::Black);

			Assert::AreEqual(Square{ 'f', '5' }, result.destination);
			Assert::AreEqual(TypeofPiece::p, result.piece.type);
			Assert::AreEqual(PieceColor::Black, result.piece.color);
			Assert::AreEqual(Square{ 'e', 0 }, result.piece.square);;
			Assert::AreEqual(true, result.captures);
			Assert::AreEqual(false, result.check);
			Assert::AreEqual(false, result.checkmate);
			Assert::AreEqual(TypeofPiece::_, result.promotion);
			Assert::AreEqual(Castle::_, result.castles);

			// Test Castles
			testString = "O-O";
			result = moveStringParse(testString, PieceColor::Black);

			Assert::AreEqual(Square{ 0, 0 }, result.destination);
			Assert::AreEqual(TypeofPiece::_, result.piece.type);
			Assert::AreEqual(PieceColor::Black, result.piece.color);
			Assert::AreEqual(Square{ 0, 0 }, result.piece.square);;
			Assert::AreEqual(false, result.captures);
			Assert::AreEqual(false, result.check);
			Assert::AreEqual(false, result.checkmate);
			Assert::AreEqual(TypeofPiece::_, result.promotion);
			Assert::AreEqual(Castle::Short, result.castles);

			// Test Promotion
			testString = "e1=R#";
			result = moveStringParse(testString, PieceColor::Black);

			Assert::AreEqual(Square{ 'e', '1' }, result.destination);
			Assert::AreEqual(TypeofPiece::p, result.piece.type);
			Assert::AreEqual(PieceColor::Black, result.piece.color);
			Assert::AreEqual(Square{ 0, 0 }, result.piece.square);;
			Assert::AreEqual(false, result.captures);
			Assert::AreEqual(false, result.check);
			Assert::AreEqual(true, result.checkmate);
			Assert::AreEqual(TypeofPiece::R, result.promotion);
			Assert::AreEqual(Castle::_, result.castles);
		}

	};
}
