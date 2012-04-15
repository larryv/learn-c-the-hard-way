#!/usr/bin/env ruby

require "test/unit"

class Stack
  def initialize
    @stack = []
  end

  def push(obj)
    @stack.push obj
  end

  def pop
    @stack.pop
  end

  def peek
    @stack.last
  end

  def empty?
    @stack.empty?
  end
end

class TestStack < Test::Unit::TestCase
  def setup
    @s = Stack.new
  end

  def test_new_stack_is_empty
    assert_equal true, @s.empty?
  end

  def test_pushing_makes_stack_not_empty
    @s.push 13
    assert_equal false, @s.empty?
  end

  def test_popping_returns_correct_result
    @s.push 42
    assert_equal 42, @s.pop
    assert_equal true, @s.empty?
  end

  def test_popping_from_empty_stack_fails
    assert_nil @s.pop
  end

  def test_peeking_does_not_pop
    @s.push 69
    assert_equal 69, @s.peek
    assert_equal false, @s.empty?
  end
end
