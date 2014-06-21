class PlayerRecordsController < ApplicationController
  before_action :set_player_record, only: [:show, :edit, :update, :destroy]

  # GET /player_records
  # GET /player_records.json
  def index
    @player_records = PlayerRecord.all
  end

  # GET /player_records/1
  # GET /player_records/1.json
  def show
  end

  # GET /player_records/new
  def new
    @player_record = PlayerRecord.new
  end

  # GET /player_records/1/edit
  def edit
  end

  # POST /player_records
  # POST /player_records.json
  def create
    @player_record = PlayerRecord.new(player_record_params)

    respond_to do |format|
      if @player_record.save
        format.html { redirect_to @player_record, notice: 'Player record was successfully created.' }
        format.json { render action: 'show', status: :created, location: @player_record }
      else
        format.html { render action: 'new' }
        format.json { render json: @player_record.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /player_records/1
  # PATCH/PUT /player_records/1.json
  def update
    respond_to do |format|
      if @player_record.update(player_record_params)
        format.html { redirect_to @player_record, notice: 'Player record was successfully updated.' }
        format.json { head :no_content }
      else
        format.html { render action: 'edit' }
        format.json { render json: @player_record.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /player_records/1
  # DELETE /player_records/1.json
  def destroy
    @player_record.destroy
    respond_to do |format|
      format.html { redirect_to player_records_url }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_player_record
      @player_record = PlayerRecord.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def player_record_params
      params.require(:player_record).permit(:player, :score)
    end
end
