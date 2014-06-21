require 'test_helper'

class PlayerRecordsControllerTest < ActionController::TestCase
  setup do
    @player_record = player_records(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:player_records)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create player_record" do
    assert_difference('PlayerRecord.count') do
      post :create, player_record: { player: @player_record.player, score: @player_record.score }
    end

    assert_redirected_to player_record_path(assigns(:player_record))
  end

  test "should show player_record" do
    get :show, id: @player_record
    assert_response :success
  end

  test "should get edit" do
    get :edit, id: @player_record
    assert_response :success
  end

  test "should update player_record" do
    patch :update, id: @player_record, player_record: { player: @player_record.player, score: @player_record.score }
    assert_redirected_to player_record_path(assigns(:player_record))
  end

  test "should destroy player_record" do
    assert_difference('PlayerRecord.count', -1) do
      delete :destroy, id: @player_record
    end

    assert_redirected_to player_records_path
  end
end
