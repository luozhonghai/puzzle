class ServerController < ApplicationController
	skip_before_filter :verify_authenticity_token
	def getScore
		@player = PlayerRecord.find_by(player: params[:player])
    respond_to do |format|
      format.json { render :inline => @player.to_json  }
    end
	end

	def setScore
		@player = PlayerRecord.find_by(player: params[:player])
		if(@player.score < params[:score].to_i)
			@player.score = params[:score]
			@player.save
		end
		respond_to do |format|
      format.json { render :inline => @player.to_json  }
    end
	end

	def getHighScore
		maxScore = PlayerRecord.maximum(:score)
		@player = PlayerRecord.find_by(score: maxScore)
		respond_to do |format|
      format.json { render :inline => @player.to_json  }
    end
	end
end
